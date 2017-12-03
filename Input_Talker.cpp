#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include "pathify/ReturnCoordinate.h"
#include <cstdlib>

struct Coordinate
    {
        float x;
        float y;
        float z;
    };

struct Item
{
    std::string maze_name;
    std::string item_name;
    Coordinate location;
};

std::vector<Item> Robot_RAM;

/*output string format:
Maze Name;Item Name;Item x-location;Item y-location;Item z-location */
std::string Item_Information;

/*provided by the current maze name*/
std::string maze_name;
ros::ServiceClient client;

bool found_before(std::string item_name);
bool is_empty(std::ifstream& pFile);
float string_to_float(std::string str);
Item parse_string_To_Item(std::string item_stringform);

std::string change_to_lowercase(std::string str);
std::string float_to_string(float flt);
std::vector<std::string> parse_input(std::string str);
std::vector<std::string> parse_output_from_ros(std::string str);
std::string parse_Item_To_string(Item item);

void go_mode(std::string item_name);
void find_mode(std::string item_name);
void update_rom(const std::string& file_name, const std::string& content);
void update_ram(const std::string& filen_name);
void add_item_to_file(std::string item);

int main(int argc, char **argv)
{
    
    bool end = false;
    update_ram("Robot_ROM.txt");
    maze_name = /*get from somewhere*/"love";
    
    ros::init(argc, argv, "Input_Talker");
    ros::NodeHandle n;
    client = n.serviceClient<pathify::ReturnCoordinate>("coordinate");
    
    
    
    
    while(!end)
    {
        std::string input;
        std::cout<<"What do you want me to do?"<<"\n";
        getline(std::cin, input);
        std::vector<std::string> input_vector;
        input_vector = parse_input(input);
        int size = input_vector.size();
        
        if(size == 3) /*e.g "Go to LocationAA" */
        {
            if(change_to_lowercase(input_vector[0])== "go" )
            {
                if(!found_before(change_to_lowercase(input_vector[2])))
                {
                    std::cout<<" location not know. Should I find?"<<"\n";
                    std::cout<<"y/n: ";
                    std::string responds;
                    getline(std::cin, responds);
                    std::vector<std::string> in;
                    in = parse_input(responds);
                    if(change_to_lowercase(in[0]) == "y")
                    {
                        find_mode(input_vector[2]);
                    }
                    else{
                        continue;
                    }
                    
                }
                else
                {
                    go_mode(input_vector[2]); 
                }
            }
            else
            {
                std::cout<<"I don't know that command! Maybe start with go."<<"\n";  
            }
        }
        
        else if (size == 2) /*e.g,  "find locationAA" */
        {
            if (change_to_lowercase(input_vector[0]) == "find") 
            {
                if(!found_before(change_to_lowercase(input_vector[1]))) 
                {
                    find_mode(input_vector[1]);
                }
                else
                {
                    std::cout<<" Location already found before. Should I go?"<<"\n"; 
                    std::cout<<"y/n: ";
                    std::string responds;
                    getline(std::cin, responds);
                    std::vector<std::string> in;
                    in = parse_input(responds);
                    if(change_to_lowercase(in[0]) == "y")
                    {
                        go_mode(input_vector[1]);
                    }
                    else{
                        continue;
                    }
                }
            }
            else
            {
                std::cout<<"I don't know that command! Maybe start with find."<<"\n";  
            }
        }
        
        else if(size == 1)
        {
            if(change_to_lowercase(input_vector[0]) == "end" || change_to_lowercase(input_vector[0]) == "terminate"|| \
                    change_to_lowercase(input_vector[0]) == "stop"  || change_to_lowercase(input_vector[0]) == "quit")
            {
                break; /*terminate program*/
            }
            else
            {
                std::cout<<"I don't know that command!"<<"\n";  
            }
        }
        
        else if(size <= 0 || size >3)
        {
            std::cout<<"Too many words! I understand up to three words per command!"<<"\n";  
        }
        
    }
    std::cout<<"Shutting Down ..."<<"\n";
    std::cout<<"Done! Have a great day!"<<"\n";
    
    return 0;
}

/* goes to the area name give*/
void go_mode(std::string item_name)
{
    int size = (int) Robot_RAM.size();
    for(int i = 0; i< size; i++){
        if(Robot_RAM[i].item_name == item_name && Robot_RAM[i].maze_name == maze_name)
        {
            Coordinate x_y_z;
            x_y_z.x = Robot_RAM[i].location.x;     
            x_y_z.y = Robot_RAM[i].location.y;                                                 
            x_y_z.z = Robot_RAM[i].location.z;  
           
            /* TODO: send xyz timi*/
            std::cout<<"Going to "<<" "<< item_name+"..."<<"\n";
            std::cout<<"Goon to "<<" "<< item_name+"!"<<"\n";
            return;
            
        }
      }
    
 }


 void find_mode(std::string item_name)
{
    /*look for and add to memory*/
    Item tmp;
    bool found = false;
    tmp.maze_name = maze_name;
    tmp.item_name = change_to_lowercase(item_name);
    pathify::ReturnCoordinate srv;
    
   if (client.call(srv))
    {
        /*recieve co-ordinate from robot*/
        ROS_INFO("result: %s", srv.response.sum);
        std::string result = srv.response.coord_xyz;
        std::vector<std::string> tmp_result = parse_output_from_ros(result);
        Coordinate x_y_z;
        float size  = string_to_float(tmp_result[0]) + string_to_float(tmp_result[1]) + string_to_float(tmp_result[2]);
        if(size!= 0.0)
        {
            x_y_z.x =  string_to_float(tmp_result[0]);                           
            x_y_z.y =  string_to_float(tmp_result[1]);                          
            x_y_z.z =  string_to_float(tmp_result[2]);                          
            tmp.location = x_y_z;
            Robot_RAM.push_back(tmp);
            std::string tmp_string = parse_Item_To_string(tmp);
            update_rom("Robot_ROM.txt", tmp_string);
            std::cout<<"Found"<<" "<< item_name<<"\n";
        }
    }
}


void update_rom(const std::string& file_name, const std::string& content)
{
    std::ofstream outfile;
    outfile.open(file_name.c_str(), std::ios_base::app);
    if(outfile.is_open())
    {
        outfile<<content;
        outfile.close();
        return;
    }
    std::cout<<"could not save location to the memory"<<"\n";
}


/*reads from file/database and updat RAM Memory*/
void update_ram(const std::string& file_name)
{
    std::string line;
    std::ifstream myfile (file_name.c_str());
    if(myfile.is_open())
    {
        if(!is_empty(myfile))
        {
            while(getline(myfile, line))
            {
                Item tmp = parse_string_To_Item(line);
                Robot_RAM.push_back(tmp);
                }
        
        }
        myfile.close();
    }
    
}

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

std::string parse_Item_To_string(Item item)
{
    std::string fin;
    fin = item.maze_name + ";"+ item.item_name + ";" + float_to_string(item.location.x)+ ";" + \
    float_to_string(item.location.y)+ ";" + float_to_string(item.location.z) + "."+"\n";
    return fin;
}


std::vector<std::string> parse_helper(std::string str)
{
    int size = str.length();
    std::string a;
    std::vector<std::string> output;
    for(int i = 0; i<size; i++)
    {
        if (str[i] ==  ';' || str[i] ==  '.')
        {
            output.push_back(a);
            a = "";
        }
        else
        {
            a += str[i];
        }
    }
    
    return output; 
}

std::vector<std::string> parse_output_from_ros(std::string str)
{
    int size = str.length();
    std::string a;
    std::vector<std::string> output;
    for(int i = 0; i<size; i++)
    {
        if (str[i] ==  ',' || str[i] ==  '.')
        {
            output.push_back(a);
            a = "";
        }
        else
        {
            a += str[i];
        }
    }
    
    return output; 
}


Item parse_string_To_Item(std::string item_stringform)
{
    Item tmp;
    std::vector<std::string> items;
    Coordinate x_y_z;
    
    items = parse_helper(item_stringform);
    
    tmp.maze_name = items[0];
    tmp.item_name = items[1];
    
    x_y_z.x =   string_to_float(items[2]); 
    x_y_z.y =   string_to_float(items[3]);                                         
    x_y_z.z =   string_to_float(items[4]); 
    
    tmp.location = x_y_z;
    
    return tmp;
}

bool found_before(std::string item_name)
{ 
    int size = (int) Robot_RAM.size();
    for(int i = 0; i< size; i++){
        if(Robot_RAM[i].item_name == item_name && Robot_RAM[i].maze_name == maze_name)
        {
            return true;
        }
    }
    return false;
}

std::string change_to_lowercase(std::string str)
{
    int size = str.length();
    std::string a;
    for(int i = 0; i<size; i++){
        a += tolower(str[i]);
    }
    return a;
}

float string_to_float(std::string str)
{
    std::string::size_type sz;     // alias of size_t
    float flt= std::stof (str,&sz);
    return flt;
}

std::string float_to_string(float flt)
{
    return std::to_string(flt);
}

std::vector<std::string> parse_input(std::string str)
{
    int size = str.length();
    std::string a;
    std::vector<std::string> output;
    for(int i = 0; i<size; i++)
    {
        if (!isspace(str[i]))
        {
            a += str[i];
            
        }
        else
        {  if(a!="")
            {
                output.push_back(a);
                a = "";
            }
            
        }
    }
    if(a!="")
    {
        output.push_back(a);
        a = "";
    }
    
    return output;
}

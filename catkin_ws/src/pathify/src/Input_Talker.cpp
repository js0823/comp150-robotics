#include <vector>
#include <sstream>
#include <string>
#include <fstream>

struct Coordinate
    {
        float x;
        float y;
        float z;
    };

struct Item
{
    std::string maze_name;
    std:string item_name;
    Coordinate location;
};

std::vector<Item> Robot_RAM;

/*output string format:
Maze Name; Item Name; Item x-location; Item y-location; Item z-location */
std::string Item_Information;

/*provided by the current maze name*/
std::string maze_name;

bool found_before(std::string item_name);
float string_to_float(std::string str);
std::string float_to_string(float flt);
void add_item_to_file(std::string item);
std::string parse_Item_To_string(Item item);
Item parse_string_To_Item(std::string item_stringform);
std::string change_to_lowercase(std::string str);
void go_mode(std::string item_name);
void find_mode(std::string item_name);
void update_rom(const std::string& file_name, const std::string& content);
void update_ram(const std::string& filen_name, const std::string& content);

int main(int argc, char **argv)
{
    bool end = false;
    std::string input;
    maze_name = /*get from somewhere*/"love";
    std::cout<<"What do you want me to do?"<<"\n";
    while(getline(cin, input))
    {
        std::vector<std::string> input_vector;
        parse_input(input, input_vector);
        int size = input_vector.size();
        
        if(size = 3) /*e.g "Go to LocationAA" */
        {
            if(change_to_lowercase(input_vector[0])== "go" )
            {
                if(!found_before(change_to_lowercase(input_vector[2])))
                {
                    std::cout<<" location not know. Should I find?"<<"\n";
                    std::cout<<"y/n: ";
                    std::string responds;
                    std::cin>>responds;
                    if(change_to_lowercase(responds) == "y")
                    {
                        find_mode(input_vector[2]));
                    }
                }
                else
                {
                    go_mode(input_vector[2])); 
                }
            }
        }
        
        else if (size = 2) /*e.g,  "find locationAA" */
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
                        std::cin>>responds;
                        if(change_to_lowercase(responds) == "y")
                        {
                            go_mode(input_vector[1]));
                        }
                    }
                }
            }
        std::cout<<"What do you want me to do?"<<"\n";
    }
    
    return 0;
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


std::string parse_Item_To_string(Item item)
{
    std::string fin;
    fin = item.maze_name + ";"+ item.item_name + ";" + float_to_string(item.location.x)+ ";" + \
                    float_to_string(item.location.y)+ ";" + float_to_string(item.location.z) + ".";
    return fin;
}


std::vector<std::string> parse_helper(std::string str)
{
    int size = str.length();
    std::string a;
    std::vector<std::string> output;
    for(int i = 0; i<size; i++)
    {
        if (str[i] ==  ";" || str[i] ==  ".")
        {
            output.push_back(a)
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
    Coordinate xyz;
    tmp.maze_name = items[0];
    tmp.item_name = items[1];
    
    /*recieve co-ordinate from robot*/
    xyz.x =   0.0                                              //get from timi
    xyz.y =     0.0                                            //get from timi
    xyz.z =    0.0                                             //get from timi
    tmp.location = xyz;
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


void go_mode(std::string item_name)
{
    int size = (int) Robot_RAM.size();
    for(int i = 0; i< size; i++){
        if(Robot_RAM[i].item_name == item_name && Robot_RAM[i].maze_name == maze_name)
        {
            // 
            Coordinate xyz;
            xyz.x = Robot_RAM[i].location.x;     
            xyz.y = Robot_RAM[i].location.y;                                                 
            xyz.z = Robot_RAM[i].location.z;  
            // send to timi
            
        }
      }
    
 }

void find_mode(std::string item_name)
{
    /*look for and add to memory*/
    Item tmp;
    Coordinate xyz;
    tmp.maze_name = maze_name;
    tmp.item_name = change_to_lowercase(item_name);
    /*recieve co-ordinate from robot*/
    xyz.x =  0.0                           //get from timi
    xyz.y =  0.0                           //get from timi
    xyz.z =   0.0                          //get from timi
    tmp.location = xyz;
    if(/*valid location*/true)
    {
        Robot_RAM.push_back(tmp);
    }
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
void update_rom(const std::string& file_name, const std::string& content)
{
    std::ofstream outfile;
    outfile.open(file_name);
    outfile<<content;
    outfile.close();
}
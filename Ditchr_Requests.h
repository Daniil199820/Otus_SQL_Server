#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <memory>
//enum COMMANDS{INSERT, TRUNCATE, INTERSECTION, SYMMETRIC_DIFFERENCE};

class Data_storage{
public:
    void insert(std::list<std::string>& args){
        
        auto arguments = args;  
       // auto cnt = tables.count(arguments.front());
        auto it = tables.find(arguments.front());
        std::cout<<"DA\n";  
        if(it!=tables.end()){
            std::cout<< "Element is finded!\n";
        }
        else{
            std::cout<<"Element isn't finded!\n";
        }
        arguments.pop_front();
        Table current_table = it->second;
        auto it_second = current_table.find(std::stoi(arguments.front()));
        //arguments.pop_front();
        if(it_second==current_table.end()){
            std::cout << "OK\n";
            current_table[std::stoi(arguments.front())] = arguments.back();
        }
        else{
            std::cout << "Duplicate";
        }
    }

    void truncate(std::list<std::string>& args){
        
    }

    void intersection(std::list<std::string>& args){
        
    }

    void symmetric_difference(std::list<std::string>& args){
    
    }

private:
    using Table = std::unordered_map<const int,std::string,std::hash<int>>;
    Table A;
    Table B;
    std::unordered_map<const std::string, Table,std::hash<int>> tables = {{"A",A},{"B",B}};
};

class ICommand {
public:
    virtual void execute(std::list<std::string>& args) = 0;
    virtual ~ICommand() = default;
};

class Command : public ICommand {
public:
    virtual ~Command() = default;
protected:
    Command(std::shared_ptr<Data_storage> d):data_store(d){}
    std::shared_ptr<Data_storage> data_store;
};

class InsertCommand: public Command{
public:
    InsertCommand(std::shared_ptr<Data_storage> d): Command(d){}

    void execute(std::list<std::string>& args) override {
        if(args.size()==3){
            std::cout<<"Correct number of arguments\n";
            data_store->insert(args);
        }
        else{
            std::cout<<"Uncorrect number of arguments(Should be 3)\n";
        }
    }
};

class TruncateCommand: public Command{
public:
    TruncateCommand(std::shared_ptr<Data_storage> d): Command(d){}

    void execute(std::list<std::string>& args) override{
        if(args.size()==1){
            std::cout<<"Correct number of arguments\n";
            data_store->truncate(args);
        }
        else{
            std::cout<<"Uncorrect number of arguments(Should be 1)\n";
        }
    }
};

class IntersectionCommand: public Command{
public:
    IntersectionCommand(std::shared_ptr<Data_storage> d): Command(d){}

    void execute(std::list<std::string>& args) override{
        if(args.size()==0){
            std::cout<<"Correct number of arguments\n";
            data_store->intersection(args);
            
        }
        else{
            std::cout<<"Uncorrect number of arguments(Should be 0)\n";
        }
    }
};

class SymmetricCommand: public Command{
public:
    SymmetricCommand(std::shared_ptr<Data_storage> d): Command(d){}

    void execute(std::list<std::string>& args) override{
        if(args.size()==0){
            std::cout<<"Correct number of arguments\n";
            data_store->symmetric_difference(args);
        }
        else{
            std::cout<<"Uncorrect number of arguments(Should be 0)\n";
        }
    }
};



class Request_manager{
public:
    Request_manager(){
        data_ = std::make_shared<Data_storage>();
    }

    void set_request(const std::string& str_command){
        std::vector<Command*> commands;
        auto list_words =  parce_function(str_command);
        
        commands.push_back(commands_dict.at(list_words.front()));
        list_words.pop_front();
        for(auto& it:commands){
            it->execute(list_words);
        }  
    }

private:
    
    std::shared_ptr<Data_storage> data_;

    std::map<const std::string, Command*> commands_dict = {
        {"INSERT", new InsertCommand(data_)},
        {"TRUNCATE", new TruncateCommand(data_)},
        {"INTERSECTION", new IntersectionCommand(data_)},
        {"SYMMETRIC_DIFFERENCE", new SymmetricCommand(data_)}
    };
    //std::map<const std::string, Command*> commands_dict={};
    

    std::list<std::string> parce_function(const std::string& str_){
        std::list<std::string> temp_splitted = split(str_,' ');
        
        if(!temp_splitted.empty()){
        }
        
        if( temp_splitted.empty()){
            //throw ("use tabulations for splitting"); 
        }

        return temp_splitted;
    }

    std::list<std::string> split(const std::string &str, char d)
    {
	    std::list<std::string> r;

	    std::string::size_type start = 0;
	    std::string::size_type stop = str.find_first_of(d);
	    while (stop != std::string::npos)
	    {
		    r.push_back(str.substr(start, stop - start));

		    start = stop + 1;
		    stop = str.find_first_of(d, start);
	    }

	    r.push_back(str.substr(start));

	    return r;
    }

};


 /*   Document doc;

    std::vector<Command *> history;
    history.push_back(new NewDocumentCommand(&doc));
    history.push_back( new ParagraphCommand(&doc, "Manual"));
    history.push_back( new ParagraphCommand(&doc, ""));
    history.push_back( new ParagraphCommand(&doc, "Hello, World!"));
    history.push_back( new SaveAsCommand(&doc, "hello.doc"));

    for(auto c: history) {
        c->execute();
    }
    */
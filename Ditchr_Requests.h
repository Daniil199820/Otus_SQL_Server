#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>

//enum COMMANDS{INSERT, TRUNCATE, INTERSECTION, SYMMETRIC_DIFFERENCE};

class Data_storage{
public:
    void insert(){
        std::cout<<"super\n";
    }

    void truncate(){

    }

    void intersection(){

    }

    void symmetric_difference(){

    }

};

class ICommand {
public:
    virtual void execute() = 0;
    virtual ~ICommand() = default;
};

class Command : public ICommand {
public:
    virtual ~Command() = default;
protected:
    Command(Data_storage* d):data_store(d){}
    Data_storage* data_store;
};

class InsertCommand: public Command{
public:
    InsertCommand(Data_storage* d): Command(d){}

    void execute() override {
        data_store->insert();
    }
};

class TruncateCommand: public Command{
public:
    TruncateCommand(Data_storage* d): Command(d){}

    void execute() override{
        data_store->truncate();
    }
};

class IntersectionCommand: public Command{
public:
    IntersectionCommand(Data_storage* d): Command(d){}

    void execute() override{
        data_store->intersection();
    }
};

class SymmetricCommand: public Command{
public:
    SymmetricCommand(Data_storage* d): Command(d){}

    void execute() override{
        data_store->symmetric_difference();
    }
};

//struct Column{
//    enum Type{} type;
//    std::string name;
//};

class Request_manager{
public:
    Request_manager() = default;

    void set_request(const std::string& str_command){
        std::vector<Command*> commands;
        auto vector_words =  parce_function(str_command);

        commands.emplace_back(commands_dict.at(vector_words[0]));   
        for(auto& it:commands){
            it->execute();
        }  
    }

private:
    Data_storage data_;

    std::map<const std::string, Command*> commands_dict = {
        {"INSERT", new InsertCommand(&data_)},
        {"TRUNCATE", new TruncateCommand(&data_)},
        {"INTERSECTION", new IntersectionCommand(&data_)},
        {"SYMMETRIC_DIFFERENCE", new SymmetricCommand(&data_)}
    };
    //std::map<const std::string, Command*> commands_dict={};
    

    std::vector<std::string> parce_function(const std::string& str_){
        std::vector<std::string> temp_splitted = split(str_,' ');
        
        if(!temp_splitted.empty()){
        }
        
        if( temp_splitted.empty()){
            //throw ("use tabulations for splitting"); 
        }

        return temp_splitted;
    }

    std::vector<std::string> split(const std::string &str, char d)
    {
	    std::vector<std::string> r;

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
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

enum COMMANDS{INSERT, TRUNCATE, INTERSECTION, SYMMETRIC_DIFFERENCE};

class Data_table{
public:
    void insert(){

    }

    void truncate(){

    }

    void intersection(){

    }

    void symmetric_difference(){

    }

};

class Command{

};

class Request_manager{
public:
    void set_request(const std::string& str_command){
        //std::cout <<  
    }

private:
    std::unordered_map<const std::string, Command*> commands_dict;

    void parce_function(const std::string& str_){
        std::vector<std::string> temp_splitted = split(str_,'   ');
        
        if( temp_splitted.empty()){
            //throw ("use tabulations for splitting"); 
        }

        

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


// Команда (Command)

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>


class Document {
public:
    void create() {
        std::cout << "new document" << std::endl;
    }

    void paragraph(const std::string &text) {
        m_text += text + "\n";
        std::cout << "new paragraph " << text << std::endl;
    }

    void save_as(const std::string &name) {
        std::cout << "--- " << name << "---" << std::endl;
        std::cout << m_text << std::endl;
    }
private:
    std::string m_text;
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
    Command(Document *d)
        : document(d) {

    }
    Document * document;
};


class NewDocumentCommand: public Command {
public:
    NewDocumentCommand(Document * d) 
        : Command(d) {

    }

    void execute() override {
        document->create();
    }
};


class ParagraphCommand: public Command { 
public:
    ParagraphCommand(Document * d, const std::string &text_) 
        : Command(d)
        , m_text(text_) {

    }

    void execute() override {
        document->paragraph(m_text);
    }
private:
    std::string m_text;
};


class SaveAsCommand: public Command {
public:
    SaveAsCommand(Document * d, const std::string &fname_) 
        : Command(d)
        , m_fname(fname_) {

    }

    void execute() override {
        document->save_as(m_fname);
    }
private:
    std::string m_fname;
};



#pragma region (ControllerExample)
class Controller {
public:
    void scheduleCommand(std::unique_ptr<Command> cmdPtr) {
        // lock
        m_commands.emplace_back(std::move(cmdPtr));
        // add to history
        // unlock
    }
private:
    void workerThread() {
        // wait for command
        for (auto& cmd : m_commands)
            cmd->execute();
        // execute command
    }

    std::list<std::unique_ptr<Command>> m_commands;
};


class EmptyCommand : public ICommand {
    void execute() override {
    }
};

class Button {
public:
    Button(const std::string& name) 
        : m_name{name},
        m_command{std::make_unique<EmptyCommand>()} {

    }

    Button(const std::string& name, std::unique_ptr<ICommand> cmdPtr)
        : m_name{name}
        , m_command{std::move(cmdPtr)} {

    }

    void draw() {

    }

    void press() {
        m_command->execute();
    }

private:
    std::unique_ptr<ICommand> m_command;
    std::string m_name;
};
#pragma endregion (ControllerExample)

int main() {
    Document doc;

    std::vector<Command *> history;
    history.push_back(new NewDocumentCommand(&doc));
    history.push_back( new ParagraphCommand(&doc, "Manual"));
    history.push_back( new ParagraphCommand(&doc, ""));
    history.push_back( new ParagraphCommand(&doc, "Hello, World!"));
    history.push_back( new SaveAsCommand(&doc, "hello.doc"));

    for(auto c: history) {
        c->execute();
    }

    Button emptyButton{"empty"};
    emptyButton.press();

    return 0;
}
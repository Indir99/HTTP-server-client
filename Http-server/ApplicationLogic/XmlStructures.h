#pragma once

#include <string>
#include <iostream>

struct Header{
    std::string senderAddress;
    std::string receiverAddress;
    void print(){
        std::cout<<" Sender Address: "<<senderAddress<<std::endl;
        std::cout<<" Response should be sent to address: "<<receiverAddress<<std::endl;
    }
};

struct ProbeData {
    Header header;
    std::string deviceName;
    void print(){
        header.print();
        std::cout<<" Device type: "<< deviceName <<std::endl;
    }
};

struct DatabaseData {
    Header header;
    std::string databaseText;
    void print(){
        header.print();
        std::cout<<" Database request text: "<<databaseText<<std::endl;
    }
};

struct SubscribeData {
    Header header;
    std::string listOfReports;
    void print(){
        header.print();
        std::cout<<" Client subscribed to following reports: " << listOfReports <<std::endl;
    }
};

struct UnsubscribeData {
    Header header;
    std::string unsubText;
};

struct StartReportsData{
    Header header;
    std::string command;
    void print(){
        header.print();
        std::cout<<" Command received in StartReports message: "<< command <<std::endl;
    }
};

struct ReportTypeAdata {
    Header header;
    std::string responseText;
    void print(){
        header.print();
        std::cout<<" Response message: "<<responseText<<std::endl;
    }
};

struct ReportTypeBdata {
    Header header;
    std::string responseText;
    void print(){
        header.print();
        std::cout<<" Response message: "<<responseText<<std::endl;
    }
};

struct SetCommandOneData{
    Header header;
    std::string patiendID;
    std::string operation;
    std::string time;
    void print(){
        header.print();
        std::cout<<" Patient ID: "<<patiendID <<std::endl;
        std::cout<<" Operation: "<<operation << std::endl;
        std::cout<<" Time: "<< time <<std::endl;
    }
};

struct SetCommandTwoData{
    Header header;
    std::string patiendID;
    std::string operation;
    std::string opValue;
    std::string time;
    void print(){
        header.print();
        std::cout<<" Patient ID: "<<patiendID <<std::endl;
        std::cout<<" Operation: "<<operation << std::endl;
        std::cout<<" New value: "<<opValue<<std::endl;
        std::cout<<" Time: "<< time <<std::endl;
    }
};

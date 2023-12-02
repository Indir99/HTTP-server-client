#pragma once

#include <string>
#include <iostream>

struct Header{
    std::string senderAddress;
    std::string receiverAddress;
    void print(){
        std::cout<<"Sender Address: "<<senderAddress<<std::endl;
        std::cout<<"Response should be sent to address: "<<receiverAddress<<std::endl;
    }
};

struct ProbeMatchData {
    Header header;
    std::string deviceName;
    void print(){
        header.print();
        std::cout<<" Device type: "<< deviceName <<std::endl;
    }
};

struct DatabaseResponseData {
    Header header;
    std::string patientText;
    std::string doctorText;
    std::string therapyText;
    void print(){
        header.print();
        std::cout<<"GetDatabase reponse info: " <<std::endl;
        std::cout<<"Patient info: "<< patientText <<std::endl;
        std::cout<<"Doctor info: "<< doctorText <<std::endl;
        std::cout<<"Therapy info: "<< therapyText <<std::endl;

    }
};

struct SubscribResponseData {
    Header header;
    std::string listOfReports;
    void print(){
        header.print();
        std::cout<<"Server approved subscription for following reports: " << listOfReports <<std::endl;
    }
};

struct UnsubscribeResponseData {
    Header header;
    std::string unsubText;
};

struct StoppingReportsData{
    Header header;
    std::string command;
    void print(){
        header.print();
        std::cout<<"Command received in Stopping reports message: "<< command <<std::endl;
    }
};

struct ReportTypeAdata {
    Header header;
    std::string patientID;
    std::string patientFirstName;
    std::string patientLastName;
    std::string bloodPressure;
    std::string temperature;
    std::string heartRate;
    std::string time;
    void print(){
        header.print();
        std::cout<<" Patient ID: "<< patientID<<std::endl;
        std::cout<<" Patient Name: "<<patientFirstName<<std::endl;
        std::cout<<" Patient Last name: "<<patientLastName<<std::endl;
        std::cout<<" Blood Pressure: "<<bloodPressure <<std::endl;
        std::cout<<" Temperature: "<<temperature<<std::endl;
        std::cout<<" Heart Rate: "<<heartRate<<std::endl;
        std::cout<<"Measurement time: "<<time<<std::endl;
    }
};

struct ReportTypeBdata {
    Header header;
    std::string patientID;
    std::string patientFirstName;
    std::string patientLastName;
    std::string doctorID;
    std::string doctorFirstName;
    std::string doctortLastName;
    std::string therapyName;
    std::string therapyStatus;
    std::string time;
    void print(){
        header.print();
        std::cout<<" Patient ID: "<< patientID<<std::endl;
        std::cout<<" Patient Name: "<<patientFirstName<<std::endl;
        std::cout<<" Patient Last name: "<<patientLastName<<std::endl;
        std::cout<<" Doctor ID: "<< doctorID<<std::endl;
        std::cout<<" Doctor Name: "<<doctorFirstName<<std::endl;
        std::cout<<" Doctor Last name: "<<doctortLastName<<std::endl;
        std::cout<<" Therapy name: "<<therapyName<<std::endl;
        std::cout<<" Therapy status: "<<therapyStatus<<std::endl;
        std::cout<<" Report time: "<<time<<std::endl;
    }
};

struct SetCommandOneResponseData {
    Header header;
    std::string responseText;
    void print(){
        header.print();
        std::cout<<"Response message: "<<responseText<<std::endl;
    }
};

struct SetCommandTwoResponseData {
    Header header;
    std::string responseText;
    void print(){
        header.print();
        std::cout<<"Response message: "<<responseText<<std::endl;
    }
};

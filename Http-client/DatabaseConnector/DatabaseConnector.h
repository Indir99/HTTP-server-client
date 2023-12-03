#pragma once

#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

namespace DatabaseConnector {

class DatabaseConnector {
public:
    DatabaseConnector(std::string path, std::string username, std::string password) :
        m_path{path}, m_username{username}, m_password{password},
        driver{sql::mysql::get_mysql_driver_instance()}{
    }
    ~DatabaseConnector(){
        delete con;
    }

    void Connect(){
        try{
            con = driver->connect("tcp://localhost:3306/ClientDatabase", "indir", "Iceking99."); // Replace with your MySQL server address, username, and password
            con->setSchema("ClientDatabase");
        } catch (...) {
            throw std::runtime_error("Can't connect to DB");
        }
    }

    void SelectAndPrintTypeA(){
        // Fetch data from table
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet*result = stmt->executeQuery("SELECT * FROM ReportAdatabase");
        std::cout << "\nData from ReportAdatabase:\n";
        while (result->next()) {
            std::cout << "ID: " << result->getInt("ID")
                      << ", PatientID: " << result->getString("PatientID")
                      << ", Name: " << result->getString("PatientFirstName") << " " << result->getString("PatientLastName")
                      << ", Blood Pressure: " << result->getString("BloodPressure")
                      << ", Temperature: " << result->getString("Temperature")
                      << ", Heart Rate: " << result->getInt("HeartRate")
                      << ", Time: " << result->getString("CurrentTime") << std::endl;
        }

        delete result;
        delete stmt;
    }

    void SelectAndPrintTypeB(){
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet*result = stmt->executeQuery("SELECT * FROM ReportBdatabase");

        std::cout << "\nData from ReportBdatabase:\n";
        while (result->next()) {
            std::cout << "ID: " << result->getInt("ID")
                      << ", PatientID: " << result->getString("PatientID")
                      << ", Name: " << result->getString("PatientFirstName") << " " << result->getString("PatientLastName")
                      << ", DoctorID: " << result->getString("DoctorID")
                      << ", Doctor Name: " << result->getString("DoctorFirstName") << " " << result->getString("DoctorLastName")
                      << ", Therapy Name: " << result->getString("TherapyName")
                      << ", Therapy Status: " << result->getString("TherapyStatus")
                      << ", Time: " << result->getString("CurrentTime") << std::endl;
        }
        delete result;
        delete stmt;
    }

    void insertIntoReportAdatabase(const std::string& patientID,
                                   const std::string& patientFirstName,
                                   const std::string& patientLastName,
                                   const std::string& bloodPressure,
                                   const std::string& temperature,
                                   const std::string& heartRate,
                                   const std::string& currentTime) {
        // Prepare the INSERT statement
        sql::PreparedStatement *stmtA =
            con->prepareStatement("INSERT INTO ReportAdatabase (PatientID, PatientFirstName, PatientLastName, BloodPressure, Temperature, HeartRate, CurrentTime) VALUES (?, ?, ?, ?, ?, ?, ?)");

        // Bind parameters
        stmtA->setString(1, patientID);
        stmtA->setString(2, patientFirstName);
        stmtA->setString(3, patientLastName);
        stmtA->setString(4, bloodPressure);
        stmtA->setString(5, temperature);
        stmtA->setString(6, heartRate);
        stmtA->setString(7, currentTime);

        // Execute the INSERT statement
        stmtA->executeUpdate();

        std::cout << "Data inserted into ReportAdatabase successfully.\n";

        delete stmtA;
    }

    void insertIntoReportBdatabase(const std::string& patientID,
                                   const std::string& patientFirstName,
                                   const std::string& patientLastName,
                                   const std::string& doctorID,
                                   const std::string& doctorFirstName,
                                   const std::string& doctorLastName,
                                   const std::string& therapyName,
                                   const std::string& therapyStatus,
                                   const std::string& currentTime) {
        // Prepare the INSERT statement
        sql::PreparedStatement *stmtB =
            con->prepareStatement("INSERT INTO ReportBdatabase (PatientID, PatientFirstName, PatientLastName, DoctorID, DoctorFirstName, DoctorLastName, TherapyName, TherapyStatus, CurrentTime) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");

        // Bind parameters
        stmtB->setString(1, patientID);
        stmtB->setString(2, patientFirstName);
        stmtB->setString(3, patientLastName);
        stmtB->setString(4, doctorID);
        stmtB->setString(5, doctorFirstName);
        stmtB->setString(6, doctorLastName);
        stmtB->setString(7, therapyName);
        stmtB->setString(8, therapyStatus);
        stmtB->setString(9, currentTime);

        // Execute the INSERT statement
        stmtB->executeUpdate();

        std::cout << "Data inserted into ReportBdatabase successfully.\n";

        delete stmtB;
    }

private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    std::string m_path;
    std::string m_username;
    std::string m_password;
};

}

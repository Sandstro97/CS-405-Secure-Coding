// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>

std::string getCurrentTimestamp() {
    // make timestamp (yyyy-mm-dd)
    // This function uses C++ 20 and needs /std::c++latest enabled
    // in Visual Studio 2019's project properties
    const std::chrono::time_point<std::chrono::system_clock> now{
        std::chrono::system_clock::now()
    };
    const std::chrono::year_month_day ymd{
        std::chrono::floor<std::chrono::days>(now)
    };

    std::stringstream s;
    s << std::format("{:0>4}", static_cast<int>(ymd.year())) << "-" << std::format("{:0>2}", static_cast<unsigned>(ymd.month())) << "-" << std::format("{:0>2}", static_cast<unsigned>(ymd.day()));
    return s.str();
}

/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// <returns>transformed string</returns>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    // get lengths now instead of calling the function every time.
    // this would have most likely been inlined by the compiler, but design for perfomance.
    const auto key_length = key.length();
    const auto source_length = source.length();

    // assert that our input data is good
    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // loop through the source string char by char
    for (size_t i = 0; i < source_length; ++i)
    { // TODO: student need to change the next line from output[i] = source[i]
      // transform each character based on an xor of the key modded constrained to key length using a mod
        output[i] = source[i] ^ key[i % key_length];
    }

    // our output length must equal our source length
    assert(output.length() == source_length);

    // return the transformed string
    return output;
}

std::string read_file(const std::string& filename)
{
    std::string file_text = "John Q. Smith\nThis is my test string";

    // TODO: implement loading the file into a string
    try {
        // Use try block to "open" the file
        std::ifstream inFile(filename);
        std::stringstream stringStream;

        // Try to read from the file
        stringStream << inFile.rdbuf();

        // Add the file contents to the string
        file_text = stringStream.str();

        // close the file
        inFile.close();
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR in read_file!\nIssue: " << e.what() << std::endl;
    }

    return file_text;
}

std::string get_student_name(const std::string& string_data)
{
    std::string student_name;

    // find the first newline
    size_t pos = string_data.find('\n');
    // did we find a newline
    if (pos != std::string::npos)
    { // we did, so copy that substring as the student name
        student_name = string_data.substr(0, pos);
    }

    return student_name;
}

void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
    //  TODO: implement file saving
    //  file format
    //  Line 1: student name
    //  Line 2: timestamp (yyyy-mm-dd)
    //  Line 3: key used
    //  Line 4+: data
    const std::string timestamp = getCurrentTimestamp();

    try {
        std::ofstream outFile(filename);
        outFile << student_name << std::endl;
        outFile << timestamp << std::endl;
        outFile << key << std::endl;
        outFile << data << std::endl;

        outFile.close();
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR in save_data_file!\nIssue: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Encyption Decryption Test!" << std::endl;

    // input file format
    // Line 1: <students name>
    // Line 2: <Lorem Ipsum Generator website used> https://pirateipsum.me/ (could be https://www.lipsum.com/ or one of https://www.shopify.com/partners/blog/79940998-15-funny-lorem-ipsum-generators-to-shake-up-your-design-mockups)
    // Lines 3+: <lorem ipsum generated with 3 paragraphs> 
    //  Fire in the hole bowsprit Jack Tar gally holystone sloop grog heave to grapple Sea Legs. Gally hearties case shot crimp spirits pillage galleon chase guns skysail yo-ho-ho. Jury mast coxswain measured fer yer chains man-of-war Privateer yardarm aft handsomely Jolly Roger mutiny.
    //  Hulk coffer doubloon Shiver me timbers long clothes skysail Nelsons folly reef sails Jack Tar Davy Jones' Locker. Splice the main brace ye fathom me bilge water walk the plank bowsprit gun Blimey wench. Parrel Gold Road clap of thunder Shiver me timbers hempen halter yardarm grapple wench bilged on her anchor American Main.
    //  Brigantine coxswain interloper jolly boat heave down cutlass crow's nest wherry dance the hempen jig spirits. Interloper Sea Legs plunder shrouds knave sloop run a shot across the bow Jack Ketch mutiny barkadeer. Heave to gun matey Arr draft jolly boat marooned Cat o'nine tails topsail Blimey.

    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrytpteddatafile.txt";
    const std::string source_string = read_file(file_name);
    const std::string key = "password";

    // get the student name from the data file
    const std::string student_name = get_student_name(source_string);

    // encrypt sourceString with key
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // save encrypted_string to file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // decrypt encryptedString with key
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // save decrypted_string to file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;

    // students submit input file, encrypted file, decrypted file, source code file, and key used
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

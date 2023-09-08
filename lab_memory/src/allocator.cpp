/**
 * @file allocator.cpp
 * Implementation of the Allocator class.
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "allocator.h"
#include "fileio.h"

Allocator::Allocator(const std::string& studentFile, const std::string& roomFile)
{
    createLetterGroups();
    loadStudents(studentFile);
    loadRooms(roomFile);        // Error with line 47 2 times, 53 once
}

void Allocator::createLetterGroups()
{
    // Make letters (A - Z lettergroups)
    alpha = new Letter[26];
    for (int i = 0; i < 26; i++)
        alpha[i].letter = 'A' + i;
}

void Allocator::loadStudents(const std::string& file)
{
    // Read in students
    fileio::loadStudents(file);
    studentCount = fileio::getNumStudents();

    for (int i = 0; i < studentCount; i++) {
        std::string name = fileio::nextStudent();
        char letter = name[0];
        int index = (int)letter - 'A';
        alpha[index].addStudent();
    }
}

void Allocator::loadRooms(const std::string& file)
{
    // Read in rooms
    fileio::loadRooms(file);
    roomCount = fileio::getNumRooms();
    rooms = new Room[roomCount];    

    totalCapacity = 0;
    int i = 0;
    //std::cout << "While loop start" << std::endl;
    while (fileio::areMoreRooms()) {
        rooms[i] = fileio::nextRoom();      //ERROR with line 18
        totalCapacity += rooms[i].capacity; // Error
        i++; 
    }
    //std::cout << "While loop end" << std::endl;
}


void Allocator::printStudents(std::ostream & stream /* = std::cout */)
{
    // Output number of each last letter name
    stream << "Student counts (" << studentCount << " total)" << std::endl;
    for (int i = 0; i < 26; i++)
        stream << alpha[i].letter << ": " << alpha[i].count << std::endl;
}

void Allocator::allocate()
{
    // Perform the allocation
    int border = solve();

    // Check for an error
    if (border < 0) {
        std::cerr << std::endl << "Cannot allocate all students." << std::endl << std::endl;
        exit(-1);
    }
}

void Allocator::printRooms(std::ostream & stream /* = std::cout */)
{
    // Output the allocation
    stream << "Room Allocation (" << studentCount << "/" << totalCapacity << ")"
         << std::endl;
    for (int i = 0; i < roomCount; i++)
        rooms[i].print(stream);
}

int Allocator::solve()
{
    std::stable_sort(alpha, alpha + 26);

    for (int L = 0; L < 26; L++) {
        //std::cout << "Switching room to largest opening" << std::endl;
        Room* r = largestOpening();
        r->addLetter(alpha[L]);
    }

    return minSpaceRemaining();
}

int Allocator::minSpaceRemaining()
{
    int border = 1000000;
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].spaceRemaining() < border)
            border = rooms[i].spaceRemaining();
    return border;
}

Room* Allocator::largestOpening()
{
    int index = 0;
    int max_remaining = rooms[0].spaceRemaining();
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].spaceRemaining() > max_remaining) {
            index = i;
            max_remaining = rooms[i].spaceRemaining();
        }
    }
    return &rooms[index];
}

Allocator::~Allocator() {
    delete[] rooms;
    delete[] alpha;
}

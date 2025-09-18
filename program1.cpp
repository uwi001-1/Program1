#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

/*********************************************************************
File name: program1.cpp
Author: KRIPA HAYANJU
Date: 09/18/2025

Purpose:
    The program reads movie data from a file and stores it in an array of structures. 
    It allows tracking the number of times each movie has been watched, computes the total runtime of all movies, and identifies the least-watched movie.
Command Parameters:
    No parameters to main().
Input:
    The user provides the file name, selects movies to watch by entering their serial number, and exit the program by typing “quit".
Results:
    The program displays the list of movies, along with the total runtime of all movies and the title of the least-watched movie.
Notes:
    The program uses stoi function to turn string into integer. The program will allow invalid input and coninue running till the user inputs "quit".
*********************************************************************/


struct Movie   //defining the Movie structure
{
    string szTitle;       //Title name
    string szDirector;    //Director's name
    int iRuntime;        //Runtime of the movie 
    int iWatched;        // No. of times watched 
    int iYear;           //Year of the movie release
};


/*********************************************************************
void Changetospaces(string& szWord);
Purpose:
    Changes underscores into spaces of a word.
Parameters:
    I/O string& szWord - string that needs change. 
Return Value:
    N/A
Notes:
    N/A
*********************************************************************/
void Changetospaces(string& szWord)
{
    int iLength = szWord.size();
    for(int i =0; i<iLength; ++i)
    {
        if(szWord[i] == '_'){
            szWord[i] = ' ';
        }
    }
}


/*********************************************************************
bool loadMovies(string& szFilename, Movie moviesArr[], int& iSize); 
Purpose:
    Reads movie information from a file and stores it in an array of movie structure.
Parameters:
    I string& szFilename – name of the file to load movie data from.
    O Movie moviesArr[] – array where movie data will be stored.
    O int& iSize – number of movies loaded from the file.
Return Value:
    It returns either true or false.
Notes:
    It uses the Changetospaces function.
*********************************************************************/
bool loadMovies(string& szFilename, Movie moviesArr[], int& iSize)  
{
    ifstream fileInput;
    fileInput.open(szFilename);  
    
    if(!fileInput)
    {
        return false;          //if file doesn't exist return false
    }
    
    fileInput >> iSize;      //read file size      
    for(int i = 0; i < iSize; ++i)   //reads the further details of the file 
    {
        fileInput >> moviesArr[i].szTitle;
        fileInput >> moviesArr[i].szDirector;
        fileInput >> moviesArr[i].iRuntime;
        fileInput >> moviesArr[i].iWatched;
        fileInput >> moviesArr[i].iYear;

        Changetospaces(moviesArr[i].szTitle);
        Changetospaces(moviesArr[i].szDirector);
    }
    fileInput.close();    //Close the file

    return true;
}


/*********************************************************************
void displayMovies(const Movie moviesArr[], int iSize);
Purpose:
    Dispalys the array of movie structures as defined as the header.
Parameters:
    I const Movie moviesArr[] – an array of movie structures containing the data to be displayed. The const means the function only reads the array, it doesn’t modify it.
    I int iSize – the total number of movies stored in the array.
Return Value:
    N/A
Notes:
    It uses setw(), which is set width to give characters width for the next thing we output.
*********************************************************************/
void displayMovies(const Movie moviesArr[], int iSize)
{
    cout << left  //the header
        << setw(3) << "N"
        << setw(25) << "Title"
        << setw(20) << "Director"
        << setw(8) << "Runtime"
        << setw(10) << "Watched"
        << setw(6) << "Year"
        << endl;

    for(int i = 0; i < iSize; ++i)    //display the movie with the loop
    {
        cout << left     
            << setw(3) << i
            << setw(25) <<  moviesArr[i].szTitle
            << setw(20) <<  moviesArr[i].szDirector
            << setw(8) <<  moviesArr[i].iRuntime
            << setw(10) <<  moviesArr[i].iWatched
            << setw(6) <<  moviesArr[i].iYear
            << endl;
    }
}


/*********************************************************************
void watchMovie(Movie moviesArr[], int iSize, int iMovieIndex);
Purpose:
    Takes the moivie index and increments the number of time that movie is watched.
Parameters:
    I/O Movie moviesArr[] – the array of movies; the function updates the iWatched field of the selected movie.
    I int iSize – the number of movies in the array.
    I int iMovieIndex – the index of the movie the user wants to watch.
Return Value:
    N/A
Notes:
    N/A
*********************************************************************/
void watchMovie(Movie moviesArr[], int iSize, int iMovieIndex)  //int iSize is not required
{
    ++moviesArr[iMovieIndex].iWatched;
}


/*********************************************************************
int calculateTotalRuntime(const Movie moviesArr[], int iSize);
Purpose:
    Calcualtes the total runtime of all the movies in the array of moive structure.
Parameters:
    I const Movie moviesArr[] – array of movies whose runtimes will be summed; marked const because it’s not modified.
    I int iSize – number of movies in the array.
Return Value:
    int - the total runtime of all movies in the array. 
Notes:
    N/A
*********************************************************************/
int calculateTotalRuntime(const Movie moviesArr[], int iSize)
{
    int iTotalRuntime = 0;
    for(int i = 0; i < iSize; ++i)
    {
        iTotalRuntime = iTotalRuntime + moviesArr[i].iRuntime;
    }

    return iTotalRuntime;
}


/*********************************************************************
int findLeastWatched(const Movie moviesArr[], int iSize)
Purpose:
    Finds the index of the least watched movie by comparing the watched time.
Parameters:
    I const Movie moviesArr[] – array of movies to check; the function only reads this array.
    I int iSize – number of movies in the array.
Return Value:
    int – the index of the movie that has been watched the least number of times.
Notes:
    N/A
*********************************************************************/
int findLeastWatched(const Movie moviesArr[], int iSize)
{
    int iLeastWatched = 0;
    for(int i = 1; i < iSize; ++i)
    {
        if(moviesArr[i].iWatched < moviesArr[iLeastWatched].iWatched)
        {
            iLeastWatched = i;
        }
    }
    return iLeastWatched;  //return index of the least watched movie 
}


int main()
{
    string szFilename;
    int iNumMovies;
    Movie moviesArr[200];

    cout << "Please enter a file to open: ";
    cin >> szFilename;

    bool iLoading = loadMovies(szFilename, moviesArr, iNumMovies);
    if(!iLoading)   //if the file doesn't exist or not found, exit the program
    {
        cout << szFilename << " not found. Exiting program" << endl;
        return -1;
    }

    displayMovies(moviesArr, iNumMovies);  //dispaly movies

    string szAns;
    int iJustNum = 0;
    do
    {
        cout << endl;
        cout << "Enter the movie number to watch (or \"quit\"): ";
        cin >> szAns;

        if(szAns == "quit")  //if user wants to ouput
        {
            cout << endl <<"Total runtime of all movies: ";
            cout << calculateTotalRuntime(moviesArr, iNumMovies) << endl;
            cout << "Least watched movie: ";
            cout << moviesArr[findLeastWatched(moviesArr, iNumMovies)].szTitle << endl;
            iJustNum = 1;
        }
        else
        {
            try  //if user user inputs other number except "quit"
            {
                int iNum = stoi(szAns);  
                if(iNum >= 0 && iNum < iNumMovies)
                {
                    watchMovie(moviesArr, iNumMovies, iNum);
                    displayMovies(moviesArr, iNumMovies);
                }
                else
                {
                    cout << "No movie to watch." << endl;
                    displayMovies(moviesArr, iNumMovies);
                    continue;
                }
            }
            catch(invalid_argument&)  //if user inputs other than integer and "quit"
            {
                cout << "No movie to watch." << endl;
                displayMovies(moviesArr, iNumMovies);
            }
            
        }

    } while(iJustNum == 0);  //end the loop after the user inputs "quit"

    return 0;
}

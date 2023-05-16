//
//  mazequeue.cpp
//  CS32 HW2
//
//  Created by Arash Dewan on 5/2/23.
//

#include <iostream>
#include <queue>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};



bool pathExists(char maze[][10], int sr, int sc, int er, int ec)

{
    queue<Coord> coordStack;
    Coord start(sr, sc);
    coordStack.push(start);
    maze[sr][sc] = '*';
    while (!coordStack.empty())
    {
        //pop top coordinate
        Coord current = coordStack.front();
        cout << current.r();
        cout << current.c();
        cout << endl;
        coordStack.pop();
        //if current equal to ending, we have solved the maze
        if (current.c() == er && current.r() == er)
        {
            return true;
        }
        //check each place you can move (s, e, n, w);
        Coord S(current.r()+1, current.c());
        Coord E(current.r(), current.c()+1);
        Coord N(current.r()-1, current.c());
        Coord W(current.r(), current.c()-1);
        //check to move S
        if (maze[S.r()][S.c()] == '.')
        {
            coordStack.push(S);
            maze[S.r()][S.c()] = '*';
        }
        //check to move E
        if (maze[E.r()][E.c()] == '.')
        {
            coordStack.push(E);
            maze[E.r()][E.c()] = '*';
        }
        //check to move N
        if (maze[N.r()][N.c()] == '.')
        {
            coordStack.push(N);
            maze[N.r()][N.c()] = '*';
        }
        //check to move W
        if (maze[W.r()][W.c()] == '.')
        {
            coordStack.push(W);
            maze[W.r()][W.c()] = '*';
        }
        
    }
    //no solution
    return false;
    
}

//int main()
//{
//
//    char maze[10][10] = {
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','.','.','X','.','.','.','.','X' },
//        { 'X','.','.','X','X','.','X','X','.','X' },
//        { 'X','.','X','.','.','.','.','X','X','X' },
//        { 'X','X','X','X','.','X','X','X','.','X' },
//        { 'X','.','.','X','.','.','.','X','.','X' },
//        { 'X','.','.','X','.','X','.','.','.','X' },
//        { 'X','X','.','X','.','X','X','X','X','X' },
//        { 'X','.','.','.','.','.','.','.','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//
//    if (pathExists(maze, 3,4, 8,1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//    return 0;
//}


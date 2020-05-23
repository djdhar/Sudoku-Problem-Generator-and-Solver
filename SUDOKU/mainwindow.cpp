#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QVector>
#include<QTimer>
using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<QVector<int>> board;

inline void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

int randRange(int low, int high)
{
    return (int)(rand() / (RAND_MAX / (double)(high - low))) + low;
}

void delArr(int arr[], int size, int pos)
{
    for(int i=pos+1; i<size; i++)
        swap(arr[i], arr[i-1]);
}


void Print(QVector<QVector<int>>& board){
   /*
    cout<<endl;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board.size();j++){
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
      cout<<endl;
      */
    }


int randomGenerator(int num);
bool unUsedInBox(int rowStart, int colStart, int num,QVector<QVector<int>> &board, int N, int K, int SRN);
bool unUsedInRow(int i,int num,QVector<QVector<int>> &board, int N, int K, int SRN) ;
bool unUsedInCol(int j,int num,QVector<QVector<int>> &board, int N, int K, int SRN) ;
bool CheckIfSafe(int i,int j,int num,QVector<QVector<int>> &board, int N, int K, int SRN) ;

void fillBox(int row,int col,QVector<QVector<int>> &board, int N, int K, int SRN) ;
void fillDiagonal(QVector<QVector<int>> &board, int N, int K, int SRN) ;
void removeKDigits(QVector<QVector<int>> &board, int N, int K, int SRN);
bool fillRemaining(int i, int j,QVector<QVector<int>> &board, int N, int K,int SRN) ;
void fillValues(QVector<QVector<int>> &board, int N, int K, int SRN);


    QVector<QVector<int>> Sudoku(int N, int K)
    {

        int SRN = 3;
        QVector<QVector<int>> board;
        board.resize(N);
        for(int i=0;i<N;i++)
            board[i].resize(N);
        fillValues(board,N,K,SRN);
        return board;
    }

    void fillValues(QVector<QVector<int>> &board, int N, int K, int SRN)
    {
        fillDiagonal(board,  N,  K,  SRN);
        fillRemaining(0, SRN,board,  N,  K,SRN);
        removeKDigits(board,  N, K, SRN);
    }

    void fillDiagonal(QVector<QVector<int>> &board, int N, int K, int SRN)
    {

        for (int i = 0; i<N; i=i+SRN)
            fillBox(i, i,board,N,K,SRN);
    }

    bool unUsedInBox(int rowStart, int colStart, int num,QVector<QVector<int>> &board, int N, int K, int SRN)
    {
        for (int i = 0; i<SRN; i++)
            for (int j = 0; j<SRN; j++)
                if (board[rowStart+i][colStart+j]==num)
                    return false;

        return true;
    }

    void fillBox(int row,int col,QVector<QVector<int>> &board, int N, int K, int SRN)
    {
        int num;
        for (int i=0; i<SRN; i++)
        {
            for (int j=0; j<SRN; j++)
            {
                do
                {
                    num = randomGenerator(N);
                }
                while (!unUsedInBox(row, col, num,board,N,K,SRN));

                board[row+i][col+j] = num;
            }
        }
    }

    int randomGenerator(int num)
    {
        return rand()%num+1;
    }

    bool CheckIfSafe(int i,int j,int num,QVector<QVector<int>> &board, int N, int K, int SRN)
    {
        return (unUsedInRow(i, num,board,N,K,SRN) &&
                unUsedInCol(j, num,board,N,K,SRN) &&
                unUsedInBox(i-i%SRN, j-j%SRN, num,board,N,K,SRN));
    }

    bool unUsedInRow(int i,int num,QVector<QVector<int>> &board, int N, int K, int SRN)
    {
        for (int j = 0; j<N; j++)
           if (board[i][j] == num)
                return false;
        return true;
    }

    bool unUsedInCol(int j,int num,QVector<QVector<int>> &board, int N, int K, int SRN)
    {
        for (int i = 0; i<N; i++)
            if (board[i][j] == num)
                return false;
        return true;
    }
    bool fillRemaining(int i, int j,QVector<QVector<int>> &board, int N, int K,int SRN)
    {
        if (j>=N && i<N-1)
        {
            i = i + 1;
            j = 0;
        }
        if (i>=N && j>=N)
            return true;

        if (i < SRN)
        {
            if (j < SRN)
                j = SRN;
        }
        else if (i < N-SRN)
        {
            if (j==(int)(i/SRN)*SRN)
                j =  j + SRN;
        }
        else
        {
            if (j == N-SRN)
            {
                i = i + 1;
                j = 0;
                if (i>=N)
                    return true;
            }
        }

        for (int num = 1; num<=N; num++)
        {
            if (CheckIfSafe(i, j, num,board,N,K,SRN))
            {
                board[i][j] = num;
                if (fillRemaining(i, j+1,board,N,K,SRN))
                    return true;

                board[i][j] = 0;
            }
        }
        return false;
    }


    void removeKDigits(QVector<QVector<int>> &board, int N, int K, int SRN)
    {
        int count = K;
        while (count != 0)
        {

           int i = randomGenerator(N)-1;
           int j = randomGenerator(N)-1;
            if (board[i][j] != 0)
            {
                count--;
                board[i][j] = 0;
            }
        }
    }



    bool isUnSolved(QVector<QVector<int>>& board, int& i, int& j){
        for(i=0;i<board.size();i++){
            for(j=0;j<board.size();j++){
                if(board[i][j]==0)
                    return true;
            }
        }
        return false;
    }
    bool isSafe(QVector<QVector<int>>& board, int row, int col, int cr){
        if(board[row][col]!=0) return false;
        for(int i=0;i< board.size() ;i++){
            if(board[row][i]==cr) return false;
            if(board[i][col]==cr) return false;
        }
        int r=(row/3)*3;
        int c=(col/3)*3;
        for(int i=r;i<r+3;i++){
            for(int j=c;j<c+3;j++){
                if(board[i][j]==cr) return false;
            }
        }

        return true;
    }

    bool MainWindow::Solve(QVector<QVector<int>>& board){
        int row, col;
        if(!isUnSolved(board,row,col)) return true;
        for(int x=1;x<=9;x++){
            if(isSafe(board,row,col,x)){
                board[row][col]=x;
                SolutionProjection(board);
                delay(5);
                if(Solve(board)) return true;
                board[row][col]=0;

                SolutionProjection(board);
                delay(5);
            }
        }
        return false;
    }


void MainWindow::Free(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            QTableWidgetItem *pCell = ui->tableWidget->item(i, j);
            if(!pCell)
                {
                    pCell = new QTableWidgetItem;
                    ui->tableWidget->setItem(i, j, pCell);
                }
            //pCell->setFlags(Qt::ItemIsEditable);
            pCell->setText("");
        }
    }
}
void MainWindow::Projection(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            QTableWidgetItem *pCell = ui->tableWidget->item(i, j);
            if(!pCell)
                {
                    pCell = new QTableWidgetItem;
                    ui->tableWidget->setItem(i, j, pCell);
                }
            if(board[i][j]!=0){

                    pCell->setTextColor(QColor(255,0,0));

                    pCell->setFlags(pCell->flags() &  ~Qt::ItemIsEditable);
                    pCell->setText(QString::number(board[i][j]));
            }
        }
    }
}

void MainWindow::SolutionProjection(QVector<QVector<int>> &track){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j]==0 && track[i][j]!=0){
                QTableWidgetItem *pCell = ui->tableWidget->item(i, j);
                if(!pCell)
                    {
                        pCell = new QTableWidgetItem;
                        ui->tableWidget->setItem(i, j, pCell);
                    }
                pCell->setTextColor(QColor(0,0,255));

                pCell->setFlags(pCell->flags() &  ~Qt::ItemIsEditable);
                pCell->setText(QString::number(track[i][j]));
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    Free();
    int k = ui->spinBox->value();
    board = Sudoku(9,k);
    Print(board);
    Projection();
}

void MainWindow::on_pushButton_2_clicked()
{
    QVector<QVector<int>> track=board;
    Solve(track);
    SolutionProjection(track);
}

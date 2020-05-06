#ifndef PVPCHESS_H
#define PVPCHESS_H

#include <QWidget>
#include<QMouseEvent>
#include<vector>
namespace Ui {
class PVPChess;
}

class PVPChess : public QWidget
{
    Q_OBJECT

public:
    explicit PVPChess(QWidget *parent = nullptr);
    ~PVPChess();

    int gameMode=1;

    int countWhoFirst = -1;
    int countPlayer1Use = -1;
    bool gameState;
    int chessBoard[15][15];//棋盘
    std::vector<int>score1;
    std::vector<int>score2;
    int whoWin;
    int moveX,moveY;
    int preX,preY;//上一步
    int step ;//步数
    std::vector<int>chessBoardX;//记录步数的X
    std::vector<int>chessBoardY;//记录步数的Y

    void gameover(int, int);
    int getChessBoard(int x,int y);
    void setChessBoard(int x,int y,int value);
    bool deleteChessBoardXY();
    void addChessBoardXY(int x,int y);
    void clearChessBoard();
    void setStep(int step);
    int getStep();
    void setWhoWin(int);

signals:
    void start_emit(int,int,int);
    void piece_emit(int,int,int);

public slots:
     void posDown(int,int,int,int);
     void synNowColor(int,int,int);

protected:
     void paintEvent(QPaintEvent *event) ;
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::PVPChess *ui;
};

#endif // PVPCHESS_H

#ifndef LINKC_GUI_H
#define LINKC_GUI_H
#include "LinkC_Label.h"
#include "linkc_types.h"
#include "p2p_client.h"
#include "HeartBeats.h"
#include "MessageRecver.h"
#include <QObject>
#include <QMap>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include <QtGui>
#include <QListWidget>

#define _FRIEND_LABEL_HEIGTH    30
#define _MESSAGE_HISTORY_HEIGTH 40

class FriendGroup : public QListWidget{
    Q_OBJECT
public:
    explicit FriendGroup(QWidget *parent = 0);
protected:
};



class LinkcFriendItem : public QLabel{
    Q_OBJECT
public:
    explicit    LinkcFriendItem(QWidget *parent = 0);
    void        setFriend(const LinkC_Friend_Data data);
    LinkC_Friend_Data GetFriend(void);
signals:
    void clicked(LinkC_Friend_Data);
protected:
    QHBoxLayout *layout;
    LinkC_Friend_Data Friend;
    virtual void mousePressEvent(QMouseEvent *event);
};



class FriendArea : public QWidget{
    Q_OBJECT
public:
    explicit FriendArea(QWidget *parent = 0);
    void AddFriendToLayout(LinkC_Friend_Data Myfriend);
    void resizeEvent(QResizeEvent *);
    void setFriendCount(const char s[]);
    void setFriendCount(int n);
    int FriendCount(void);

    LinkC_Friend_Data GetFriendDataByUID(int UID);
public slots:
    void ItemClicked(LinkC_Friend_Data);
signals:
    void ChatTo(LinkC_Friend_Data);
protected:
    int friendcount;
    QWidget     *FriendLabelArea;
    typedef QMap<int,struct LinkC_Friend_Data_t>_Map;
    _Map::const_iterator Value;
    QScrollArea *list;
    QWidget     *FriendWidget;
    QVBoxLayout *FriendLayout;
    _Map         FriendMap;
    _Map::iterator result;
};


class ChatHistoryView : public QWidget{
    Q_OBJECT
public:
    explicit ChatHistoryView(char *Name, QWidget *parent = 0);
    void AddChatMessage(QString Msg);
    void AddChatMessage(QString Msg,QString Name);
    int  GetMessageCount(void);
    void resizeEvent(QResizeEvent *);
protected:
    int MessageCount;
    QWidget     *MessageBase;
    QScrollArea *List;
    QVBoxLayout *MessageLayout;
    QString     FriendName;
};


class ChatDialog : public QWidget{
    Q_OBJECT
public:
    explicit ChatDialog(LinkC_Friend_Data MyFriend, QWidget *parent = 0);
    ~ChatDialog();
    void resizeEvent(QResizeEvent *);
    int ConnectToPeer(void);
    void P2PConnectReady(void);
    int UID;
signals:
    void Recved(const char *message);
    void StartP2PConnecting(void);
    void SendMessageToServer(LinkC_User_Request);
public slots:
    int Send(void);
    void ReadyToAccept(void);
    void ComeAHeartBeats();
    void GetFriendData(LinkC_Friend_Data);
    void P2PConnectDone(bool);
    void RecvedP2PMessage(QString);
protected:
    QPushButton *SendButton;
    QPushButton *QuitButton;
    ChatHistoryView *History;
    QTextEdit   *Input;
    QVBoxLayout *Layout;
    LinkC_Friend_Data  MyFriend;
    p2p_client   *peer;
    UDP_MessageRecver *Recver;
    HeartBeats        *HeartBeater;
    QTimer *timer;
    int MessageSize;
};

#endif

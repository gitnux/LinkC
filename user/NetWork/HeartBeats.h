#include "linkc_network_protocol.h"
#include "Csocket.h"
#include <QThread>

class HeartBeats : public QThread{
    Q_OBJECT
public:
    HeartBeats(UDP_csocket sk, QThread *parent = 0);
    void run();
signals:
    void SendError(int);        // Use ErrorCode
public slots:
    void HeartBeatsStop(void);  // 心跳停止【好吓人】
protected:
    UDP_csocket Dest;
    char *SendBuffer;
};

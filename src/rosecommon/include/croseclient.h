#ifndef _CROSECLIENT_H_
#define _CROSECLIENT_H_

#include "crosecrypt.h"
#include "cnetwork_asio.h"
#include "crosepacket.h"

class CRoseClient : public Core::CNetwork_Asio {
 public:
  CRoseClient();
  CRoseClient(tcp::socket _sock);
  virtual ~CRoseClient();

  virtual bool Send(CRosePacket* _buffer);
  virtual bool Send(uint8_t* _buffer);

 protected:
  // Callback functions
  virtual bool OnConnect();
  virtual void OnConnected();
  virtual bool OnDisconnect();
  virtual void OnDisconnected();
  virtual bool OnReceive();
  virtual bool OnReceived();
  virtual bool OnSend(uint8_t* _buffer);
  virtual void OnSent();
  virtual bool HandlePacket(uint8_t* _buffer);

  PacketCodec crypt_;
};

#endif

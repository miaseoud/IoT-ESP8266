#ifndef NTP_H
#define NTP_H
/**********************************************************************************************/
extern unsigned int localPort;      // local port to listen for UDP packets
extern IPAddress timeServer; // time.nist.gov NTP server
extern const int NTP_PACKET_SIZE; // NTP time stamp is in the first 48 bytes of the message

// A UDP instance to let us send and receive packets over UDP
extern WiFiUDP udp;
void vidNtpInit (void);
int NtpRequestTime (void);
/****************************************************************************************************/
class TimeCheck
{
  private:
    unsigned int Interval, previousMillis=0;
  public:
    // Parameterized Constructor
    TimeCheck(unsigned int Interval)
    {
      this->Interval = Interval;
    }
    bool  vidIsItTime (void);
};
#endif

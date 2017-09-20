#ifndef MAINHTML_H
#define MAINHTML_H
//html page

String form = "<HEAD>"
              "<TITLE>Basic HTML Sample Page</TITLE>"
              "</HEAD>"
              "<CENTER>"
              "<BODY BGCOLOR=Yellow>"
              "<br><br><br><br>"
              "<H1>Wi-Fi GPIO Controller</H1>"
              "<IMG SRC='http://thewindowsclub.thewindowsclubco.netdna-cdn.com/wp-content/uploads/2014/02/Delete-Wi-Fi-Network-Profiles-W8.1-1.png'>"
             // "<H4>By Mahmoud Aboul-Seoud</H4>"
              "<form action='/ON'><input type='submit' value='Turn On'></form>"
              "<form action='/OFF'><input type='submit' value='Turn Off'></form>"
              "<form action='alarm'><p>Alarm <input type='text' name='alarm' size=10 autofocus>  <input type='submit' value='Set'></form>"
              "<form action='/cancel'><input type='submit' value='Cancel Alarm'></form>"
              "</CENTER>"
              "<center>"
              "<br>"
              "<H4>Copyright 2015, by <A HREF='test'>Mahmoud Aboul-Seoud</A></H4>"
              ;
#endif

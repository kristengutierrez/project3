//
//  arp.c
//  project3
//
//  Created by Kristen Kozmary on 10/7/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stdio.h>
#include "arp.h"
#include <network.h>
#include "semaphore.h"

// unsure of how to make semaphore
semaphore *mutex = make_semaphore(1);
syscall wait(mutex);
//don't know what to put in arp table
struct arptab *arptable = NULL;
syscall signal(mutex);

//is this supposed to go in netInit?
arpDaemonID = create((void *)arpDaemon, INITSTK, 3, "ARP_DAEMON", 0);
ready(arpDaemon, 1);


//arpDaemon function
void arpDaemon(void) {
  len = read(ETH0, packet, PKTSZ); //packet is where the info will be stored

}

uchar *packet = NULL;
struct ethergram *egram = NULL;
egram = (struct ethergram *)packet; //can now access fields of ethernet frame
ntohs(egram->type);
//if egram->type == ETYPE_ARP, get destination mac address (dst)
//set up arpReceive
void arpRecv(struct packet *pkt) {
  
}

//sending data to the network, don't know how to define arpgram
//is arpgram same as arppacket?
//do we do this when we get a broadcast message for our IP?
write(ETH0, (uchar *)buf, sizeof(struct ethergram) + sizeof(struct arpgram));

//to access mac address of device
uchar buf[ETH_ADDR_LEN];
devcall control(ETH0, ETH_CTRL_GET_MAC, (ulong)buf, 0);

//to get IP address of host
nvramGet("lan_ipaddr\0");

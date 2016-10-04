//
//  arp.c
//  project3
//
//  Created by Kristen Kozmary on 10/4/16.
//  Copyright © 2016 koz. All rights reserved.
//

#include <stdio.h>
#include <stddef.h>
#define ARP_NENTRY 32
#define ARP_FREE 0
#define ARP_USED 1
#define ARP_UNRESOLVED 1
#define ARP_RESOLVED 3
#define ARP_NTHRWAIT 10
#define ARP_MAX_LOOKUP 5
#define ARP_MSG_RESOLVED 1

struct arpEntry {
  ushort state;
  struct netif *nif;
  struct netaddr hwaddr;
  struct netaddr praddr;
  uint expires;
  tid_typ waiting[ARP_NTHRWAIT];
  int count;
};





int main(int argc, const char * argv[]) {
  // insert code here...
  printf("Hello, World!\n");
    return 0;
}

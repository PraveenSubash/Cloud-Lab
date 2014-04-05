#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{
 int i,val=-1,choice,choice_id,num_doms;
 int *active_doms;
 char domain_name[40];

 virConnectPtr connect;
 virDomainPtr v_dom;

 connect = virConnectOpen("xen:///");

 if (connect == NULL) 
 {
 	fprintf(stderr, "Error opening connectection to XEN:///  \n");
        exit(1);
 }
 else
 {
	while(1)
        {
			/*Finding Active Devices*/
		num_doms=virConnectNumOfDomains(connect);
        	active_doms=malloc(sizeof(int) * num_doms);
        	num_doms = virConnectListDomains(connect, active_doms, num_doms);            	
		printf("Active Domains: \n");
        
		for (i=0;i<num_doms;i++)
		{
            	printf("  %d\n", active_doms[i]);
        	}
        	free(active_doms);

        	printf("1.Start\n2.Pause\n3.Resume\n4.Shutdown\n5.Exit\n");
            	scanf("%d",&choice);
		

            	
        
            	switch(choice)
            	{
                	case 1:/*Start*/
			system("sudo xm list");
                       	printf("Enter domain name to be started  :");
		       	scanf("%s",domain_name);
			v_dom=virDomainLookupByName(connect,domain_name);
			val=virDomainCreate(v_dom);
			if(val==0)
				printf("Success\n");
                       	else
                           	printf("Failed\n");   
                       	break;

                	case 2:/*Pause*/
			printf("\nPlease Insert the Active Domian ID: ");
            		scanf("%d",&choice_id); 
            		v_dom=virDomainLookupByID(connect,choice_id);
		       	val=virDomainSuspend(v_dom);
                       	if(val==0)
                           	printf("Success\n");
                       	else
                           	printf("Failed\n");   
                       	break;

                	case 3:/*Resume*/ 
			printf("\nPlease Insert the Active Domian ID: ");
            		scanf("%d",&choice_id); 
            		v_dom=virDomainLookupByID(connect,choice_id);
		        val=virDomainResume(v_dom);
                        if(val==0)                     
                            	printf("Success\n");
                        else
                            	printf("Failed\n");   
                        break;

                	case 4: /*Shutdown*/
			printf("\nPlease Insert the Active Domian ID: ");
            		scanf("%d",&choice_id); 
            		v_dom=virDomainLookupByID(connect,choice_id);
			val=virDomainShutdown(v_dom);
                        if(val==0)                     
                            	printf("Success\n");
                        else
                            	printf("Failed\n");   
                        break;

                	default:exit(1);
                }
        }
        virConnectClose(connect);
    }
}

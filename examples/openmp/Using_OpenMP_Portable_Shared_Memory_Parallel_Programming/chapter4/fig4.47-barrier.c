/*

   DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

   Copyright 2009 Sun Microsystems, Inc. All rights reserved.

   The contents of this file are subject to the terms of the BSD License("BSD")(the "License"). 
   You can obtain a copy of the License at: http://www.opensparc.net/pubs/t1/licenses/BSD+_License.txt

   The BSD License

   Redistribution and use in source and binary forms, with or without 
   modification, are permitted provided that the following conditions are met:

       * Redistribution of source code must retain the above copyright 
         notice, this list of conditions and the following disclaimer.
       * Redistribution in binary form must reproduce the above copyright 
         notice, this list of conditions and the following disclaimer in 
         the documentation and/or other materials provided with the 
         distribution.
       * Neither the name of Sun Microsystems, Inc. or the names of 
         contributors may be used to endorse or promote products derived 
         from this software without specific prior written permission.

   This software is provided "AS IS," without a warranty of any kind. ALL 
   EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY 
   IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR 
   NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN MICROSYSTEMS, INC. ("SUN") AND 
   ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A 
   RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES. 
   IN NO EVENT WILL SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT 
   OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR 
   PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, 
   ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF SUN HAS 
   BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

   You acknowledge that this software is not designed, licensed or intended for 
   use in the design, construction, operation or maintenance of any nuclear facility. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>

#ifdef _OPENMP
  #include <omp.h>
  #define TRUE  1
  #define FALSE 0
#else
  #define omp_get_thread_num() 0
  #define omp_get_num_threads() 1
#endif

void print_time(int TID, char *comment);

int main()
{
   int TID;
   int i, n = 10;
   int a[n], b[n], ref[n];

#ifdef _OPENMP
   (void) omp_set_dynamic(FALSE);
   if (omp_get_dynamic()) {printf("Warning: dynamic adjustment of threads has been set\n");}
   (void) omp_set_num_threads(4);
#endif

   #pragma omp parallel private(TID)
   {
   
      TID = omp_get_thread_num();

      if ( TID < omp_get_num_threads()/2 ) system("sleep 3");

      (void) print_time(TID,"before");

      #pragma omp barrier

      (void) print_time(TID,"after ");

   } /*-- End of parallel region --*/

   for (i=0; i<n; i++)
   {
       b[i] = 2*(i+1);
       ref[i] = i + b[i];
   }

   #pragma omp parallel private(i) shared(n,a,b)
   {
      #pragma omp for schedule(dynamic,1) nowait
      for (i=0; i<n; i++)
          a[i] = i;

      #pragma omp barrier

      #pragma omp for schedule(dynamic,1) nowait
      for (i=0; i<n; i++)
          a[i] += b[i];
   } /*-- End of parallel region --*/

   printf("After the parallel region\n");
   for (i=0; i<n; i++)
       printf(" a[%3d] = %6d ref[%3d] = %6d\n",i,a[i],i,ref[i]);

   return(0);
}

void print_time(int TID, char *comment)
{
   time_t tp;
   char buffer[26], mytime[9];

   (void) time(&tp);
   strcpy(&buffer[0],ctime(&tp));
  
   strncpy(&mytime[0],&buffer[11],8);
   mytime[8]='\0';

   printf("Thread %d %s barrier at %s\n",TID,comment,&mytime[0]);

   return;
}

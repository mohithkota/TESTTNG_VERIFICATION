#include <stdlib.h>
#include <stdio.h>
#include <bdduser.h>

int main (int argc, char* argv[])
{
    bdd_manager bddm = bdd_init();    

    // make 8 variables A0,B0,A1,B1,A2,B2,A3,B3,S0,S1,S2,S3,cin,M (in that order)
    bdd A0 = bdd_new_var_last(bddm);
    bdd B0 = bdd_new_var_last(bddm);
    bdd A1 = bdd_new_var_last(bddm);
    bdd B1 = bdd_new_var_last(bddm);
    bdd A2 = bdd_new_var_last(bddm);
    bdd B2 = bdd_new_var_last(bddm);
    bdd A3 = bdd_new_var_last(bddm);
    bdd B3 = bdd_new_var_last(bddm);
    bdd S0 = bdd_new_var_last(bddm);
    bdd S1 = bdd_new_var_last(bddm);
    bdd S2 = bdd_new_var_last(bddm);
    bdd S3 = bdd_new_var_last(bddm);
    bdd cin = bdd_new_var_last(bddm);
    bdd  M = bdd_new_var_last(bddm); 
    // bdd  bB0 = bdd_new_var_last(bddm);
    // bdd  bB1 = bdd_new_var_last(bddm);
    // bdd  bB2 = bdd_new_var_last(bddm);
    // bdd  bB3 = bdd_new_var_last(bddm);
    // bdd  bcin = bdd_new_var_last(bddm);
    // bdd  bM = bdd_new_var_last(bddm); 

    //selection line 

                        // F = A + B

    S0 = bdd_one(bddm);  // Assigning constant 1 to S0
    S1 = bdd_zero(bddm); // Assigning constant 0 to S1
    S2 = bdd_zero(bddm); // Assigning constant 0 to S2
    S3 = bdd_one(bddm); // Assigning constant 1 to S3
    cin = bdd_zero(bddm); // Assigning constant 0 to cin
    M = bdd_zero(bddm);   // Assigning constant 0 to M

                        // F = A - B

     S0 = bdd_zero(bddm);  // Assigning constant 0 to S0
     S1 = bdd_one(bddm); // Assigning constant 1 to S1
     S2 = bdd_one(bddm); // Assigning constant 1 to S2
     S3 = bdd_zero(bddm); // Assigning constant 0 to S3
     cin = bdd_one(bddm); // Assigning constant 1 to cin
     M = bdd_zero(bddm);   // Assigning constant 0 to M

                        //F = A . B

     S0 = bdd_one(bddm);  // Assigning constant 1 to S0
     S1 = bdd_one(bddm); // Assigning constant 1 to S1
     S2 = bdd_zero(bddm); // Assigning constant 0 to S2
     S3 = bdd_one(bddm); // Assigning constant 1 to S3
     cin = bdd_one(bddm); // Assigning constant 1 to cin
     M = bdd_zero(bddm);   // Assigning constant 0 to M


    //internal complement operations
    bdd  bB0 = bdd_not(bddm,B0);
    bdd  bB1 = bdd_not(bddm,B1);
    bdd  bB2 = bdd_not(bddm,B2);
    bdd   bB3 = bdd_not(bddm,B3);
    bdd   bcin = bdd_not(bddm,cin);
    bdd   bM = bdd_not(bddm,M);
    
    // compute F0 = ~((B0.S3.A0)+(A0.S2.~(B0)))^(~(~(B0).S1)+(S0.B0)+A0)))^(~(bcin).~(bM))
                                        
                                        //and operation
    bdd a0  = bdd_and (bddm,B0,S3);
    bdd b0  = bdd_and (bddm,a0,A0);     //(B0.S3.A0) result    
    bdd c0  = bdd_and (bddm,A0,S2);
    bdd d0  = bdd_and (bddm,c0,bB0);    //(A0.S2.bB0) result


    bdd e0  = bdd_and (bddm,bB0,S1);    //~(B0).S1)
    bdd f0  = bdd_and (bddm,S0,B0);     //(S0.B0)
    bdd g0  = bdd_and (bddm,bcin,bM);   //(~(bcin).~(bM))
                 


                                        //or operation

    bdd  h0 = bdd_or (bddm,b0,d0); //(B0.S3.A0) + (A0.S2.bB0)
    bdd  i0 = bdd_or (bddm,e0,f0); // ~(B0).S1) + (S0.B0) 
    bdd  j0 = bdd_or (bddm,i0,A0); // ~(B0).S1) + (S0.B0) + A0

                                        //not operation

    bdd bg0     = bdd_not(bddm,g0); //~((~(bcin).~(bM)))   
    bdd bh0     = bdd_not(bddm,h0); //~((B0.S3.A0) + (A0.S2.bB0))                   //neagtion opearion of the first component of the F0
    bdd bj0     = bdd_not(bddm,j0); //~(~(B0).S1) + (S0.B0) + A0)                   //neagtion opearion of the second component of the F0


                                        //xor opeartion

    bdd  k0 = bdd_xor (bddm,bh0,bj0);   //~((B0.S3.A0) + (A0.S2.bB0)) ^  ~(~(B0).S1) + (S0.B0) + A0)

    //F0 is calculated

    bdd  F0 = bdd_xor (bddm,k0,bg0);    //~((B0.S3.A0) + (A0.S2.bB0)) ^  ~(~(B0).S1) + (S0.B0) + A0)  ^ ~((~(bcin).~(bM)))   


    //F1 computation

                                        //and opeartion
    bdd a1  = bdd_and (bddm,bh0,bM);
    bdd b1  = bdd_and (bddm,a1,bcin); //(~(cn).bh0.~(M))
    bdd c1  = bdd_and (bddm,bj0,bM);  //(~((B0.S1)+(S0.B0)+A0)).bM)
    bdd d1  = bdd_and (bddm,B1,S3);
    bdd e1  = bdd_and (bddm,d1,A1);  //(B1.S3.A1)
    bdd f1  = bdd_and (bddm,A1,S2);
    bdd g1  = bdd_and (bddm,f1,bB1); //(A1.S2.~(B1))
    bdd h1  = bdd_and (bddm,bB1,S1); //(~(B1).S1)
    bdd i1  = bdd_and (bddm,S0,B1);  //(S0.B1)


                                        //or operation

    bdd j1 = bdd_or (bddm,b1,c1); // (~(cn).bh0.~(M)) + (~((B0.S1)+(S0.B0)+A0)).bM)
    bdd k1 = bdd_or (bddm,e1,g1); //  ((B1.S3.A1) + (A1.S2.~(B1))) 
    bdd l1 = bdd_or (bddm,h1,i1); 
    bdd m1 = bdd_or (bddm,l1,A1); // ((~(B1).S1) + (S0.B1) + A1)

                                        //not operation

    bdd n1 = bdd_not(bddm,j1); //negation of the ~((~(cn).bh0.~(M)) + (~((B0.S1)+(S0.B0)+A0)).bM))
    bdd o1 = bdd_not(bddm,k1); //negation of the ~(((B1.S3.A1) + (A1.S2.~(B1))))
    bdd p1 = bdd_not(bddm,m1); //negation of the ~(((~(B1).S1) + (S0.B1) + A1)))


                                         //xor opeartion

    bdd q1 = bdd_xor(bddm,n1,o1);  //~((~(cn).bh0.~(M)) + (~((B0.S1)+(S0.B1)+A0)).bM)) ^ ~(((B1.S3.A1) + (A1.S2.~(B1))))
    
    bdd F1 = bdd_xor(bddm,q1,p1);  //~((~(cn).bh0.~(M)) + (~((B0.S1)+(S0.B1)+A0)).bM)) ^ ~(((B1.S3.A1) + (A1.S2.~(B1)))) ^ ~(((~(B1).S1) + (S0.B1) + A1)))



    //F2 computation

                                                    //and opeartion

    bdd a2 = bdd_and(bddm,bB2,S1); //(~(B2) . S1)
    bdd b2 = bdd_and(bddm,S0,B2);  //(S0 . B2)
    bdd c2 = bdd_and(bddm,B2,S3);
    bdd d2 = bdd_and(bddm,c2,A2); //(B2 . S3 . A2)
    bdd e2 = bdd_and(bddm,A2,S2);
    bdd f2 = bdd_and(bddm,e2,bB2); //(A2 . S2 . ~B2))
    bdd g2 = bdd_and(bddm,b1,o1); //(~(cn) . ~((B0.S3.A0) + (A0.S2.~(B0))).~(M)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))))
    bdd h2 = bdd_and(bddm,o1,c1); // (~(((B1.S3.A1) + (A1.S2.~(B1)))) . (~((B0.S1)+(S0.B0)+A0)).bM))
    bdd i2 = bdd_and(bddm,p1,bM); // (~(((~(B1).S1) + (S0.B1) + A1))) . ~M)


                                                    //or operation

    bdd j2 = bdd_or (bddm,a2,b2);   //(~(B2) . S1) + (S0 . B2)
    bdd k2 = bdd_or (bddm,j2,A2);   //(~(B2) . S1) + (S0 . B2) + A2)
    bdd l2 = bdd_or (bddm,d2,f2);   //(B2 . S3 . A2) + (A2 . S2 . (~B2)) 
    bdd m2 = bdd_or (bddm,g2,h2);   //(~(cn) . ~((B0.S3.A0) + (A0.S2.~(B0))).~(M)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))))  +  (~(((B1.S3.A1) + (A1.S2.~(B1)))) . (~((B0.S1)+(S0.B0)+A0)).bM))
    bdd n2 = bdd_or (bddm,m2,i2);   //(~(cn) . ~((B0.S3.A0) + (A0.S2.~(B0))).~(M)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))))  +  (~(((B1.S3.A1) + (A1.S2.~(B1)))) . (~((B0.S1)+(S0.B0)+A0)).bM))  +  (~(((~(B1).S1) + (S0.B1) + A1))) . ~M)

                                                     //not operation

    bdd o2 = bdd_not(bddm,n2);       //~((~(cn) . ~((B0.S3.A0) + (A0.S2.~(B0))).~(M)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))))  +  (~(((B1.S3.A1) + (A1.S2.~(B1)))) . (~((B0.S1)+(S0.B0)+A0)).bM))  +  (~(((~(B1).S1) + (S0.B1) + A1))) . ~M))
    bdd p2 = bdd_not(bddm,k2);       //~(~(B2) . S1) + (S0 . B2) + A2)
    bdd q2 = bdd_not(bddm,l2);       //~((B2 . S3 . A2) + (A2 . S2 . (~B2)))
                                                
    
                                                    //xor operation
    bdd r2 = bdd_xor (bddm,p2,q2); //~(~(B2) . S1) + (S0 . B2) + A2) ^  ~((B2 . S3 . A2) + (A2 . S2 . (~B2))) 
   
    bdd F2 = bdd_xor (bddm,r2,o2); // ~(~(B2) . S1) + (S0 . B2) + A2) ^  ~((B2 . S3 . A2) + (A2 . S2 . (~B2)))  ^ ~((~(cn) . ~((B0.S3.A0) + (A0.S2.~(B0))).~(M)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))))  +  (~(((B1.S3.A1) + (A1.S2.~(B1)))) . (~((B0.S1)+(S0.B0)+A0)).bM))  +  (~(((~(B1).S1) + (S0.B1) + A1))) . ~M))



    //F3 computation


                                                                        // and operation 
    bdd a3 = bdd_and (bddm,B3,S3); 
    bdd b3 = bdd_and (bddm,a3,A3); //(B3.S3.A3)
    bdd c3 = bdd_and (bddm,A3,S2); 
    bdd d3 = bdd_and (bddm,c3,bB3); //(A3.S2.bB3)
    bdd e3 = bdd_and (bddm, bB3,S1); //(bB3.S1)
    bdd f3 = bdd_and (bddm,S0,B3); //(S0.B3)
    bdd g3 = bdd_and (bddm,bcin,bM);//(bcin.bM)
    bdd h3 = bdd_and (bddm,bh0,o1); 
    bdd i3 = bdd_and (bddm,h3,q2);//(bcin . bM . o1 . q2)
    bdd j3 = bdd_and (bddm,g3,i3);//(~cin . ~M . ~((B0.S3.A0) + (A0.S2.bB0)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2))))
    bdd k3 = bdd_and (bddm,o1,q2);
    bdd l3 = bdd_and (bddm,k3,bj0);
    bdd m3 = bdd_and (bddm,l3,bM); //(~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2))) . ~(~(B0).S1) + (S0.B0) + A0) . bM)
    bdd n3 = bdd_and (bddm,q2,p1); //~((B2 . S3 . A2) + (A2 . S2 . (~B2)) . ~(((~(B1).S1) + (S0.B1) + A1))))
    bdd o3 = bdd_and (bddm,n3,bM); //~((B2 . S3 . A2) + (A2 . S2 . (~B2)) . ~(((~(B1).S1) + (S0.B1) + A1))) . ~M)
    bdd p3 = bdd_and (bddm,p2,bM); //(~(~(B2) . S1) + (S0 . B2) + A2). ~M)



                                                                        // or operation
     
    bdd q3 = bdd_or (bddm,j3,m3); //  (~cin . ~M . ~((B0.S3.A0) + (A0.S2.bB0)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2)))) +  (~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2))) . ~(~(B0).S1) + (S0.B0) + A0) . bM)
    bdd r3 = bdd_or (bddm,q3,o3); //  (~cin . ~M . ~((B0.S3.A0) + (A0.S2.bB0)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2)))) +  (~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2))) . ~(~(B0).S1) + (S0.B0) + A0) . bM) +  ~((B2 . S3 . A2) + (A2 . S2 . (~B2)) . ~(((~(B1).S1) + (S0.B1) + A1))) . ~M)
    //r6 with out complement  
    bdd s3 = bdd_or (bddm,r3,p3); //  (~cin . ~M . ~((B0.S3.A0) + (A0.S2.bB0)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2)))) +  (~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2))) . ~(~(B0).S1) + (S0.B0) + A0) . bM) +  ~((B2 . S3 . A2) + (A2 . S2 . (~B2)) . ~(((~(B1).S1) + (S0.B1) + A1))) . ~M) + (~(~(B2) . S1) + (S0 . B2) + A2). ~M)
    
    bdd t3 = bdd_or (bddm,b3,d3); //  (B3.S3.A3) + (A3.S2.bB3)
    bdd u3 = bdd_or (bddm,e3,f3); //  (bB3.S1) + (S0.B3)
    bdd v3 = bdd_or (bddm,u3,A3); //  (bB3.S1) + (S0.B3) + A3


                                                                        //not opertaion
    bdd w3 = bdd_not(bddm,s3); // ~r6 
    bdd x3 = bdd_not(bddm,t3); // ~((B3.S3.A3) + (A3.S2.bB3))
    bdd y3 = bdd_not(bddm,v3); // ~((bB3.S1) + (S0.B3) + A3)


                                                                        //xor operation
    bdd z3 = bdd_xor(bddm,x3,y3); // ~((B3.S3.A3) + (A3.S2.bB3)) ^ ~((bB3.S1) + (S0.B3) + A3) 
    
    bdd F3 = bdd_xor(bddm,z3,w3); // ~((B3.S3.A3) + (A3.S2.bB3))  ^  ~((bB3.S1) + (S0.B3) + A3)  ^ (~cin . ~M . ~((B0.S3.A0) + (A0.S2.bB0)) . ~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2)))) +  (~(((B1.S3.A1) + (A1.S2.~(B1)))) . ~((B2 . S3 . A2) + (A2 . S2 . (~B2))) . ~(~(B0).S1) + (S0.B0) + A0) . bM) +  ~((B2 . S3 . A2) + (A2 . S2 . (~B2)) . ~(((~(B1).S1) + (S0.B1) + A1))) . ~M) + (~(~(B2) . S1) + (S0 . B2) + A2). ~M)


    //Ripple carry adder code 


    //0 stage
                                                //and logic
    bdd ra0 = bdd_and(bddm,A0,B0);
    bdd rb0 = bdd_and(bddm,A0,cin);  
    bdd rc0 = bdd_and(bddm,B0,cin);

                                                //or logic
    bdd rd0 = bdd_or(bddm,ra0,rb0);
    bdd carry0 =  bdd_or(bddm,rd0,rc0);              //c0 = a0.b0 + a0.cin + b0.cin

                                                //exor logic

    bdd re0 = bdd_xor(bddm,A0,B0);
    bdd sum0 = bdd_xor(bddm,re0,cin);           //sum = A0 ^ B0 ^ c0


    //1st stage 
    
                                                //and logic
    bdd ra1 = bdd_and(bddm,A1,B1);
    bdd rb1 = bdd_and(bddm,A1,carry0);  
    bdd rc1 = bdd_and(bddm,B1,carry0);

                                                //or logic
    bdd rd1 = bdd_or(bddm,ra1,rb1);
    bdd carry1 =  bdd_or(bddm,rd1,rc1);              //c1 = a1.b1 + a1.carry0 + b1.carry0

                                                //exor logic

    bdd re1 = bdd_xor(bddm,A1,B1);
    bdd sum1 = bdd_xor(bddm,re1,carry0);            //sum = A1 ^ B1 ^ c1


    //2nd stage 
    
                                                //and logic
    bdd ra2 = bdd_and(bddm,A2,B2);
    bdd rb2 = bdd_and(bddm,A2,carry1);  
    bdd rc2 = bdd_and(bddm,B2,carry1);

                                                //or logic
    bdd rd2 = bdd_or(bddm,ra2,rb2);
    bdd carry2=  bdd_or(bddm,rd2,rc2);              //c2 = a2.b2 + a2.carry1 + b2.carry1

                                                //exor logic

    bdd re2 = bdd_xor(bddm,A2,B2);
    bdd sum2 = bdd_xor(bddm,re2,carry1);       //sum = A2 ^ B2 ^ c2



    //3nd stage 
    
                                                //and logic
    bdd ra3 = bdd_and(bddm,A3,B3);
    bdd rb3 = bdd_and(bddm,A3,carry2);  
    bdd rc3 = bdd_and(bddm,B3,carry2);

                                                //or logic
    bdd rd3 = bdd_or(bddm,ra3,rb3);
    bdd carry3=  bdd_or(bddm,rd3,rc3);              //c3 = a3.b3 + a3.carry2 + b3.carry2

                                                //exor logic

    bdd re3 = bdd_xor(bddm,A3,B3);
    bdd sum3 = bdd_xor(bddm,re3,carry2);       //sum = A3 ^ B3 ^ c3 

    
    printf("-----------------------Ripple carry adder-----------------------------\n");

    // print s0,s1,s2,s3
    //printf("-----------------------printing sum0-----------------------------\n");
    //bdd_print_bdd(bddm,sum0,NULL, NULL,NULL, stdout);
    //printf("-----------------------printing sum1-----------------------------\n");
    //bdd_print_bdd(bddm,sum1,NULL, NULL,NULL, stdout);
    //printf("-----------------------printing sum2-----------------------------\n");
    //bdd_print_bdd(bddm,sum2,NULL, NULL,NULL, stdout);
    //printf("-----------------------printing sum3-----------------------------\n");
    //bdd_print_bdd(bddm,sum3,NULL, NULL,NULL, stdout);

    // are F0 and sum0 the same?
    if (F0 == sum0  )
    {
        printf("F0 is Equal with sum0\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F0,NULL, NULL,NULL, stdout);
    }

    if (F1 == sum1  )
    {
        printf("F1 is Equal with sum1\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F1,NULL, NULL,NULL, stdout);
    }

    if (F2 == sum2  )
    {
        printf("F2 is Equal with sum2\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F2,NULL, NULL,NULL, stdout);
    }

    if (F3 == sum3  )
    {
        printf("F3 is Equal with sum3\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F3,NULL, NULL,NULL, stdout);
    }


    // ripple borrow subtractor


    //0 stage
                                                //and logic
    bdd brsB0 = bdd_not(bddm,B0);
    bdd brsB1 = bdd_not(bddm,B1);
    bdd brsB2 = bdd_not(bddm,B2);
    bdd brsB3 = bdd_not(bddm,B3);


    bdd rsa0 = bdd_and(bddm,A0,brsB0);
    bdd rsb0 = bdd_and(bddm,A0,cin);  
    bdd rsc0 = bdd_and(bddm,brsB0,cin);

                                                //or logic
    bdd rsd0 = bdd_or(bddm,rsa0,rsb0);
    bdd borr0 =  bdd_or(bddm,rsd0,rsc0);              //c0 = a0.b0 + a0.cin + b0.cin

                                                //exor logic

    bdd rse0 = bdd_xor(bddm,A0,brsB0);
    bdd diff0 = bdd_xor(bddm,rse0,cin);           //sum = A0 ^ B0 ^ c0


    //1st stage 
    
                                                //and logic
    bdd rsa1 = bdd_and(bddm,A1,brsB1);
    bdd rsb1 = bdd_and(bddm,A1,borr0);  
    bdd rsc1 = bdd_and(bddm,brsB1,borr0);

                                                //or logic
    bdd rsd1 = bdd_or(bddm,rsa1,rsb1);
    bdd borr1 =  bdd_or(bddm,rsd1,rsc1);              //c0 = a0.b0 + a0.cin + b0.cin

                                                //exor logic

    bdd rse1 = bdd_xor(bddm,A1,brsB1);
    bdd diff1 = bdd_xor(bddm,rse1,borr0);           //sum = A0 ^ B0 ^ c0


    //2nd stage 
    
                                                //and logic
    bdd rsa2 = bdd_and(bddm,A2,brsB2);
    bdd rsb2 = bdd_and(bddm,A2,borr1);  
    bdd rsc2 = bdd_and(bddm,brsB2,borr1);

                                                //or logic
    bdd rsd2 = bdd_or(bddm,rsa2,rsb2);
    bdd borr2 =  bdd_or(bddm,rsd2,rsc2);              //c0 = a0.b0 + a0.cin + b0.cin

                                                //exor logic

    bdd rse2 = bdd_xor(bddm,A2,brsB2);
    bdd diff2 = bdd_xor(bddm,rse2,borr1);           //sum = A0 ^ B0 ^ c0



    //3nd stage 
    
                                                //and logic
    bdd rsa3 = bdd_and(bddm,A3,brsB3);
    bdd rsb3 = bdd_and(bddm,A3,borr2);  
    bdd rsc3 = bdd_and(bddm,brsB3,borr2);

                                                //or logic
    bdd rsd3 = bdd_or(bddm,rsa3,rsb3);
    bdd borr3 =  bdd_or(bddm,rsd3,rsc3);              //c0 = a0.b0 + a0.cin + b0.cin

                                                //exor logic

    bdd rse3 = bdd_xor(bddm,A3,brsB3);
    bdd diff3 = bdd_xor(bddm,rse3,borr2);           //sum = A0 ^ B0 ^ c0

    
    printf("-----------------------Ripple borrow subtractor-----------------------------\n");

    // print s0,s1,s2,s3
    // bdd_print_bdd(bddm,sum0,NULL, NULL,NULL, stdout);
    // bdd_print_bdd(bddm,sum1,NULL, NULL,NULL, stdout);
    // bdd_print_bdd(bddm,sum2,NULL, NULL,NULL, stdout);
    // bdd_print_bdd(bddm,sum3,NULL, NULL,NULL, stdout);

    // are F0 and sum0 the same?
    if (F0 == diff0  )
    {
        printf("F0 is Equal with diff0\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F0,NULL, NULL,NULL, stdout);
    }

    if (F1 == diff1  )
    {
        printf("F1 is Equal with diff1\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F1,NULL, NULL,NULL, stdout);
    }

    if (F2 == diff2  )
    {
        printf("F2 is Equal with diff2\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F2,NULL, NULL,NULL, stdout);
    }

    if (F3 == diff3  )
    {
        printf("F3 is Equal with diff3\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F3,NULL, NULL,NULL, stdout);
    }


    // F = A . B

    bdd AA0 = bdd_and(bddm,A0,B0);
    bdd AA1 = bdd_and(bddm,A1,B1);
    bdd AA2 = bdd_and(bddm,A2,B2);
    bdd AA3 = bdd_and(bddm,A3,B3);

    printf("-----------------------F = A . B-----------------------------\n");
    if (F0 == AA0  )
    {
        printf("F0 is Equal with A0.B0\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F0,NULL, NULL,NULL, stdout);
    }

    if (F1 == AA1  )
    {
        printf("F1 is Equal with A1.B1\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F1,NULL, NULL,NULL, stdout);
    }

    if (F2 == AA2  )
    {
        printf("F2 is Equal with A2.B2\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F2,NULL, NULL,NULL, stdout);
    }

    if (F3 == AA3  )
    {
        printf("F3 is Equal with A3.B3\n");
    }    
    else
    {
        printf("Not Equal\n");
        // print F0
        bdd_print_bdd(bddm,F3,NULL, NULL,NULL, stdout);
    }



    printf("------------------------ROBDD of the ALU 7418----------------------------\n");

    // print F0,F1,F2,F3
        //printf("------------------------F0----------------------------\n");
     //bdd_print_bdd(bddm,F0,NULL, NULL,NULL, stdout);
         //printf("------------------------F1----------------------------\n");
    //bdd_print_bdd(bddm,F1,NULL, NULL,NULL, stdout);
    	//    printf("------------------------F2----------------------------\n");
    //bdd_print_bdd(bddm,F2,NULL, NULL,NULL, stdout);
      //  printf("------------------------F3----------------------------\n");
     //bdd_print_bdd(bddm,F3,NULL, NULL,NULL, stdout);

    return(0);
}


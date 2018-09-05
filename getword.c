    /*
    Shannon Olds
    Carroll CS570 Program 1
    Due 2/9/18 at 11pm
    Lexical Analysis- take in input, count length of word, and separate the words in the file with specifications regarding metacharacter
    */

    #include "getword.h"

   	int getword(char *w){
   		int iochar;
   		int length = 0;
   		while ((iochar = getchar()) != EOF){

   			//outer if loop to disregard leading spaces
                           if(iochar != ' '){


   			//check storage size, 25 but 254 to be able to include a null terminate
   			if( length >= (STORAGE -1)){
   				*w = '\0';
   				ungetc (iochar, stdin);
   				return length;
   			}
                           //check for newline with length equal to 0 for special circumstance
                           if(iochar == '\n' && length == 0){
                                   *w = '\0';
                                   return -10;
                           }

                           //there is a newline with a length greater than 0 signaling the end of the word
                           else if(iochar == '\n' && length > 0){
                                   *w = '\0';
                                   //use ungetc in order to read the newline character after separating it from the word
                                   ungetc(iochar, stdin);
                                   return length;
                           }

                           //differentiating if the # is at the beginning of the word or not
                           //# in the middle of the word so it counts normally
                           else if( iochar == '#' && length > 0){
                                   *(w++) = iochar;
                                   length++;
                           }
                           //# is at the beginning so the word ends there and -1 is returned
                           else if(iochar == '#'){
                                   *w = iochar;
                                   *(w+1) = '\0';
                                   return -1;
                           }

   			//specification for the "|&" together
   			else if(iochar == '|'){
   				iochar = getchar();
   				if(iochar == '&'){
   					*w = '|';
   					*(w+1) = iochar;
   					*(w+2) = '\0';
   					return -2;

   				}
   				else if(length >0){
   					ungetc(iochar,stdin);
   					ungetc(iochar, stdin);
                                           *w = '\0';
                                           return length;
                                   }
                                   else{
   					ungetc(iochar,stdin);
                                           *w = '|';
                                           *(w+1) = '\0';
                                           return -1;
                                   }
   			}

   			//look to see if theres a metacharacter after the backslash to keep within the word
   			else if( iochar == '\\'){
  				iochar = getchar();
   				if(iochar == '<' || iochar == ' ' ||  iochar == '>' || iochar == '#' ||  iochar == '\\' || iochar == '|' || iochar == '&'){
   					*(w++)= iochar;
   					length++;
   				}
   				else{
   					ungetc(iochar, stdin);
   				}
   			}

   			//use metacharacters as delimitiers
   			else if(iochar == '<' ||iochar == '|' || iochar == '>' || iochar == '&'){
   				if(length > 0){
   					ungetc(iochar, stdin);
   					*w = '\0';
   					return length;
   				}
   				else{
  					*w = iochar;
   					*(w+1) = '\0';
  					return -1;
  				}
  			}





          //normal circumstances
          else{
              *w++ = iochar;
              length++;
          }
  }

          //if there is a space and the word has at least 1 letter in it then it signals the end of the word
          else if(iochar == ' ' && length > 0){
            *w = '\0';
            return length;
          }
       }

         //terminating the end of each word
           *w = '\0';
          if(length > 0)
                 return length;

         return 0;
 }

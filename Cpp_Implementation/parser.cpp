#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define SUCCESS 1
#define FAILED 0

int Program();
int Declaration();
int Assignment();
int Condition();
int Update();
int Print();
int DataType();
int Identifier();
int Arithmetic();
int Relational();
int Boolean();
int Number();
int elseIf();
int String();
int Literal();

const char *cursor;
std::string outputString;
std::string outputString1;
int jump = 0;

int main() {
    std::ifstream file("lexemes_output.txt"); 
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        
        outputString += line;
    }

    cursor = outputString.c_str(); 
    std::cout << "Inputted string: " << outputString << std::endl;
    std::cout << std::endl;
    std::cout << "Input          Action" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    if (Program() && *cursor == '\0') {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "String is successfully parsed" << std::endl;
        return 0;
    } else {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Error in parsing String" << std::endl;
        return 1;
    }
}

int Program() {
    printf("%-16s Program -> Declaration Declaration Assignment Condition Update Print\n", cursor);
    if(Declaration()){
        if(Declaration()){
            if(Condition()){
                if(Assignment()){
                    if(Update()){
                        if(Print()){
                            return SUCCESS;
                        }else{
                            return FAILED;
                        }
                    }else{
                        return FAILED;
                    }
                }else{
                    return FAILED;
                }
            }else{
                return FAILED;
            }
        }else{
            return FAILED;
        }
    }
    else{
        return FAILED;
    }
}

int Declaration() {
    if (DataType()) {
        printf("%-16s Decleration -> DataType Identifier '=' Literal ';'\n", cursor);
        if (Identifier()) { 
            if (*cursor == '='){
                cursor++;
                jump++;
                if(Literal())
                {
                    if(*cursor == ';')
                    {
                        cursor++;
                        jump++;
                        return SUCCESS;
                    }else{
                        cursor-jump;
                        jump=0;
                        return FAILED;
                    }
                }else{
                    return FAILED;
                }
            }else{
                cursor-jump;
                jump=0;
                return FAILED;
            }
        } 
        else
            return FAILED;
    }
    else {
        printf("%-16s Declaration -> $\n", cursor);
        while(jump > 0)
        {
            cursor--;
            jump--;
        }
        return SUCCESS;
    }    
}

int Assignment() {
    if (Identifier()) {
        printf("%-16s Assignment ->  Identifier '=' Arithmetic ';'\n", cursor);
        if (*cursor == '=') { 
            cursor++;
            jump++;
            if (Arithmetic()){
                if(*cursor == ';')
                {
                    cursor++;
                    jump++;
                    return SUCCESS;
                }else{
                    cursor-jump;
                    jump=0;
                    return FAILED;
                }
            }else{
                return FAILED;
            }
        } 
        else{
            cursor-jump;
            jump=0;
            return FAILED;
        }
    }
    else{
        while(jump > 0)
        {
            cursor--;
            jump--;
        }
        printf("%-16s Assignment -> $\n", cursor);
        return SUCCESS;
    }
}

int Condition() {
  printf("%-16s Condition -> if ( Arithmetic relational Literal ')' '{' PrintStatement '}'\n", cursor);
  if (*cursor == 'i') {
    jump++;
    cursor++;
    if (*cursor == 'f') {
      cursor++;
      jump++;
      if (*cursor == '(') {
        cursor++;
        jump++;
        if (Identifier()||Boolean()) {
          if (Relational()) {
            if (Literal()) {
              if (*cursor == ')') {
                cursor++;
                jump++;
                if (*cursor == '{') {
                  cursor++;
                  jump++;
                  if (Print()) {
                    if (*cursor == '}') {
                      cursor++;
                      jump++;
                      // Check for else if here instead of the literal string
                      if (*cursor == 'e') {
                        cursor++;
                        jump++;
                        if (*cursor == 'l') {
                            cursor++;
                            jump++;
                          if (*cursor == 's') {
                            cursor++;
                            jump++;
                            if (*cursor == 'e') {
                              cursor++;
                              jump++;
                              if (*cursor == '{') {
                                cursor++;
                                jump++;
                                if (Print()) {
                                  if (*cursor == '}') {
                                    cursor++;
                                    jump++;
                                    return SUCCESS;
                                  } else {
                                    cursor-jump;
                                    jump=0;
                                    return FAILED;
                                  }
                                } else {
                                  return FAILED;
                                }
                              } else {
                                cursor-jump;
                                jump=0;
                                return FAILED;
                              }
                            } else {
                                cursor-jump;
                                jump=0;
                                return FAILED;
                            }
                          } else {
                            cursor-jump;
                            jump=0;
                            return FAILED;
                          }
                        } else {
                            cursor-jump;
                            jump=0;
                          return FAILED;
                        }
                      } else {
                        // No else if, return success;
                        cursor-jump;
                        jump=0;
                        return SUCCESS;
                      }
                    } else {
                        cursor-jump;
                        jump=0;
                      return FAILED;
                    }
                  } else {
                    cursor-jump;
                        jump=0;
                    return FAILED;
                  }
                } else {
                    cursor-jump;
                        jump=0;
                  return FAILED;
                }
              } else {
                cursor-jump;
                        jump=0;
                return FAILED;
              }
            } else {
              return FAILED;
            }
          } else {
            return FAILED;
          }
        } else {
          return FAILED;
        }
      } else {
        cursor-jump;
                        jump=0;
        return FAILED;
      }
    } else {
        cursor-jump;
                        jump=0;
      return FAILED;
    }
  } else {
    printf("%-16s Condition -> $\n", cursor);
    while(jump > 0)
        {
            cursor--;
            jump--;
        }
    return SUCCESS;
  }
}


int elseIf() {
    printf("%-16s if_statement -> if ( boolean_expression ) { statementlist } else { statementlist }\n", cursor);
    if (*cursor == 'i') {
        jump++;
        cursor++;
        if (*cursor == 'f') {
            cursor++;
            jump++;
            if (*cursor == '('){
                cursor++;
                jump++;
                if (Identifier()||Boolean()) {
                    if (Relational()) {
                        if (Literal()) {
                            if (*cursor == ')') {
                                cursor++;
                                jump++;
                                if (*cursor == '{'){
                                    cursor++;
                                    jump++;
                                    if(Print()){
                                        if(*cursor == '}'){
                                            cursor++;
                                            jump++;
                                            if (*cursor == 'e') {
                                                cursor++;
                                                jump++;
                                                if (*cursor == 'l') {
                                                    cursor++;
                                                    jump++;
                                                    if (*cursor == 's') {
                                                        cursor++;
                                                        jump++;
                                                        if (*cursor == 'e') {
                                                            cursor++;
                                                            jump++;
                                                            if (*cursor == '{'){
                                                                cursor++;
                                                                jump++;
                                                                if(Print()){
                                                                    if(*cursor == '}'){
                                                                        cursor++;
                                                                        jump++;
                                                                        return SUCCESS;
                                                                    }else{
                                                                        cursor-jump;
                        jump=0;
                                                                        return FAILED;
                                                                    }
                                                                }
                                                                else{
                                                                    return FAILED;
                                                                }
                                                            }
                                                            else{
                                                                cursor-jump;
                        jump=0;
                                                                return FAILED;
                                                            }
                                                        }else{cursor-jump;
                        jump=0;
                                                            return FAILED;
                                                        }
                                                    }else{cursor-jump;
                        jump=0;
                                                        return FAILED;
                                                    }
                                                }else{cursor-jump;
                        jump=0;
                                                    return FAILED;
                                                }
                                            }else{cursor-jump;
                        jump=0;
                                                return FAILED;
                                            }
                                        }else{cursor-jump;
                        jump=0;
                                            return FAILED;
                                        }
                                    }
                                    else{
                                        return FAILED;
                                    }
                                }
                                else{cursor-jump;
                        jump=0;
                                    return FAILED;
                                }
                            }else{cursor-jump;
                        jump=0;
                                return FAILED;
                            }
                        }else{
                            return FAILED;
                        }
                    }else{
                        return FAILED;
                    }
                }else{
                    return FAILED;
                }
            }else{cursor-jump;
                        jump=0;
                return FAILED;
            }
        }else{cursor-jump;
                        jump=0;
            return FAILED;
        }
    }
    else{cursor-jump;
                        jump=0;
        return FAILED;
    }
}

int Print() {
    printf("%-16s print_statement -> print ( Literal ) ;\n", cursor);
    if (*cursor == 'p') {
        cursor++;
        jump++;
        if (*cursor == 'r') {
            cursor++;
            jump++;
            if (*cursor == 'i') {
                cursor++;
                jump++;
                if (*cursor == 'n') {
                    cursor++;
                    jump++;
                    if (*cursor == 't') {
                        cursor++;
                        jump++;
                      
                                if(String()){
                                    
                                       
                                            if(*cursor == ';'){
                                                cursor++;
                                                jump++;
                                                return SUCCESS;
                                            }
                                            else{
                                                cursor-jump;
                        jump=0;
                                                return FAILED;
                                            }
                                        
                                    
                                }else{
                                    return FAILED;
                                }
                           
                        
                    }else{cursor-jump;
                        jump=0;
                        return FAILED;
                    }
                }
                else{cursor-jump;
                        jump=0;
                    return FAILED;
                }
            }
            else{cursor-jump;
                        jump=0;
                return FAILED;
            }
        }
        else{cursor-jump;
                        jump=0;
            return FAILED;
        }
    }
    else{
        printf("%-16s print -> $\n", cursor);
        while(jump > 0)
        {
            cursor--;
            jump--;
        }
        return SUCCESS;
    }
}

int Boolean() {
    printf("%-16s boolean ->  'true' | 'false'\n", cursor);
    if (*cursor == 't') {
        cursor++;
        jump++;
        if (*cursor == 'r') {
            cursor++;
            jump++;
            if (*cursor == 'u') {
                cursor++;
                jump++;
                if (*cursor == 'e') {
                    cursor++;
                    jump++;
                    return SUCCESS;
                }else{
                    cursor-jump;
                        jump=0;
                    return FAILED;
                }
            }else{
                cursor-jump;
                        jump=0;
                return FAILED;
            }
        }else{
            cursor-jump;
                        jump=0;
            return FAILED;
        }
    }else if(*cursor == 'f'){
        cursor++;
        jump++;
        if(*cursor == 'a'){
            cursor++;
            jump++;
            if(*cursor == 'l'){
                cursor++;
                jump++;
                if(*cursor == 's'){
                    cursor++;
                    jump++;
                    if(*cursor == 'e'){
                        cursor++;
                        jump++;
                        return SUCCESS;
                    }else{
                        cursor-jump;
                        jump=0;
                        return FAILED;
                    }
                }else{
                    cursor-jump;
                        jump=0;
                    return FAILED;
                }
            }else{
                cursor-jump;
                        jump=0;
                return FAILED;
            }
        }else{
            cursor-jump;
                        jump=0;
            return FAILED;
        }
    }else{
        cursor-jump;
                        jump=0;
        return FAILED;
    }

}

int Number() {
    if (*cursor >= '0' && *cursor <= '9') {
        while (*cursor >= '0' && *cursor <= '9') {
            printf("%-16s Number -> [0-9]+\n", cursor);
            jump++;
            cursor++;
        }
        return SUCCESS;
    } else {
        cursor-jump;
                        jump=0;
        return FAILED;
    }
}

int String() {
    if (*cursor == '"') {
        cursor++; 
        jump++;
        while ((*cursor >= 'a' && *cursor <= 'z') || (*cursor >= 'A' && *cursor <= 'Z') || (*cursor >= '0' && *cursor <= '9') || *cursor == ' ') {
            cursor++;
            jump++; 
        }
        if (*cursor == '"') {
            cursor++;
            jump++;
            printf("%-16s String -> '\"' [a-zA-Z0-9\\s]+ '\"'\n", cursor);
            return SUCCESS;
        } else {
            cursor-jump;
                        jump=0;
            return FAILED; 
        }
    } else {
        cursor-jump;
                        jump=0;
        return FAILED;
    }
}

int DataType() {
    
    if (*cursor == 'i') {
        printf("%-16s DataType ->  'int'\n", cursor);
        cursor++;
        jump++;
        if (*cursor == 'n') {
            cursor++;
            jump++;
            if (*cursor == 't') {
                cursor++;
                jump++;
                return SUCCESS;
            }else{
                return FAILED;
            }
        }else{
            return FAILED;
        }
    }else if(*cursor == 'b'){
        printf("%-16s DataType -> 'boolean'\n", cursor);
        cursor++;
        jump++;
        if(*cursor == 'o'){
            cursor++;
            jump++;
            if(*cursor == 'o'){
                cursor++;
                jump++;
                if(*cursor == 'l'){
                    cursor++;
                    jump++;
                    if(*cursor == 'e'){
                        cursor++;
                        jump++;
                        if(*cursor == 'a'){
                            cursor++;
                            jump++;
                            if(*cursor == 'n'){
                                cursor++;
                                jump++;
                                return SUCCESS;
                            }else{
                                cursor-jump;
                        jump=0;
                                return FAILED;
                            }
                        }else{
                            cursor-jump;
                        jump=0;
                            return FAILED;
                        }
                    }else{
                        cursor-jump;
                        jump=0;
                        return FAILED;
                    }
                }else{
                    cursor-jump;
                        jump=0;
                    return FAILED;
                }
            }else{
                cursor-jump;
                        jump=0;
                return FAILED;
            }
        }else{
            cursor-jump;
                        jump=0;
            return FAILED;
        }
    }else if(*cursor == 's'){
        printf("%-16s DataType -> 'String'\n", cursor);
        cursor++;
        if(*cursor == 't'){
            cursor++;
            jump++;
            if(*cursor == 'r'){
                cursor++;
                jump++;
                if(*cursor == 'i'){
                    cursor++;
                    jump++;
                    if(*cursor == 'n'){
                        cursor++;
                        jump++;
                        if(*cursor == 'g'){
                            cursor++;
                            jump++;
                            return SUCCESS;
                        }else{
                            cursor-jump;
                        jump=0;
                            return FAILED;
                        }
                    }else{
                        cursor-jump;
                        jump=0;
                        return FAILED;
                    }
                }else{
                    cursor-jump;
                        jump=0;
                    return FAILED;
                }
            }else{
                cursor-jump;
                        jump=0;
                return FAILED;
            }
        }else{
            cursor-jump;
                        jump=0;
            return FAILED;
        }
    }else{
        cursor-jump;
                        jump=0;
        return FAILED;
    }

}

int Arithmetic() {
    if (Identifier()) {
        if (*cursor == '+') {
            printf("%-16s Arithmetic ->  Identifier '+' Identifier'\n", cursor);
            cursor++;
            jump++;
            if (Identifier()) {
                return SUCCESS;
            }else{
                return FAILED;
            }
        } else if (*cursor == '-') {
            printf("%-16s Arithmetic ->  Identifier '-' Identifier'\n", cursor);
            cursor++;
            jump++;
            if (Identifier()) {
                
                return SUCCESS;
            }else{
                return FAILED;
            }
        }else if (*cursor == '*') {
            printf("%-16s Arithmetic ->  Identifier '*' Identifier'\n", cursor);
            cursor++;
            jump++;
            if (Identifier()) {
                
                return SUCCESS;
            }else{
                return FAILED;
            }
        } else if (*cursor == '/') {
            printf("%-16s Arithmetic ->  Identifier '/' Identifier'\n", cursor);
            cursor++;
            jump++;
            if (Identifier()) {
                
                return SUCCESS;
            }else{
                return FAILED;
            }
        }  else {
            cursor-jump;
                        jump=0;
            return FAILED;
        }
    } else {
        return FAILED;
    }
}

int Update() {
    if (Identifier()) {
        printf("%-16s Update ->  Identifier '=' Identifier RelationalOperator Literal ';'\n", cursor);
        if (*cursor == '=') { 
            cursor++;
            jump++;
            if (Identifier()){
                if (Relational()) {
                    if (Literal()){
                        if(*cursor == ';')
                        {
                            cursor++;
                            jump++;
                            return SUCCESS;
                        }else{
                            cursor-jump;
                        jump=0;
                            return FAILED;
                        }
                    }else{
                        return FAILED;
                    }
                }else{
                    return FAILED;
                } 
            }else{
                return FAILED;
            }
        } 
        else{
            cursor-jump;
                        jump=0;
            return FAILED;
        }
    }else{
        while(jump > 0)
        {
            cursor--;
            jump--;
        }

        printf("%-16s Update -> $\n", cursor);
        return SUCCESS;
    }
}

int Relational() {
    
    if (*cursor == '>') {
        cursor++;
        jump++;
        if (*cursor == '=') {
            printf("%-16s Relational ->  '>=''\n", cursor);
            cursor++;
            jump++;
            return SUCCESS;
        }else{
            return FAILED;
        }
    }else if (*cursor == '<') {
        cursor++;
        jump++;
        if (*cursor == '=') {
            printf("%-16s Relational ->  '<=''\n", cursor);
            cursor++;
            jump++;
            return SUCCESS;
        }else{
            cursor-jump;
                        jump=0;
            return FAILED;
        }
    }
    else if (*cursor == '=') {
        cursor++;
        jump++;
        if (*cursor == '=') {
            printf("%-16s Relational ->  '==''\n", cursor);
            cursor++;
            jump++;
            return SUCCESS;
        }else{
            cursor-jump;
                        jump=0;
            return FAILED;
        }
    }else{
        return FAILED;
    }

}

int Identifier() {
    if ((*cursor >= 'a' && *cursor <= 'z') || (*cursor >= 'A' && *cursor <= 'Z') || *cursor == '_') {
        printf("%-16s Identifier -> [a-zA-Z_][a-zA-Z0-9_]*\n", cursor);
        cursor++;
        jump++;
        while ((*cursor >= 'a' && *cursor <= 'z') || (*cursor >= 'A' && *cursor <= 'Z') || (*cursor >= '0' && *cursor <= '9') || *cursor == '_') {
            cursor++;
            jump++;
        }
        return SUCCESS;
    } else {
        cursor-jump;
                        jump=0;
        return FAILED;
    }
}

int Literal() {
    if (Number() || Boolean() || String()) {
        printf("%-16s Literal -> Number | Boolean | String\n", cursor);
        return SUCCESS;
    } else {
        return FAILED;
    }
}

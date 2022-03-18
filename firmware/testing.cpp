#include <iostream>
#include <string.h>

// Define keys we can work with
struct Key {
  char* identifier;
  int code;
};
#define NUM_KEYS 5
const Key KEY_LOOKUP[NUM_KEYS] = {
  {"a",0},
  {"b",1},
  {"c",3},
  {"enter",4},
  {"plus",5}
};
// Find a key by it's name
const Key* findKey(char* id) {
  for (int i=0;i<NUM_KEYS;i++) {
    if (strcmp(KEY_LOOKUP[i].identifier,id)) {
      return &KEY_LOOKUP[i];
    }
  }
  return NULL;
}

// Define the action class
// This represents something that can happen as a result of user input
class Action {
  public:
    void execute(); // Called when the key is pressed
    void release(); // Called when the key is released
};

class KeyAction: public Action {
    private:
      int m_keyCode;
    public:
      KeyAction(int keyCode) : m_keyCode(keyCode) {}

      void execute() {
        std::cout << this->m_keyCode << " pressed\n";
      }
      void release() {
        std::cout << this->m_keyCode << " released\n";
      }
};

class ActionSequence: public Action {

  private:
    Action* m_sequence;
    bool m_atOnce;
    int m_seqLength;

  public:
    ActionSequence(Action* sequence, int seqLength, bool atOnce) : m_sequence(sequence), m_atOnce(atOnce), m_seqLength(seqLength) {}

      void execute() {
        for (int i=0;i<m_seqLength;i++) {
          m_sequence[i].execute();
          if (!m_atOnce) {
            //delay(100);
            m_sequence[i].release();
          }
        }
      }
      void release() {
        if (m_atOnce) {
          for (int i=0;i<m_seqLength;i++) {
            m_sequence[i].release();
          }
        }
      }
};

class ActionType : public Action {
  private:
    char* m_text;

  public:
    ActionType(char* text) : m_text(text) {}

    void execute() {
      std::cout << "Typing: " << m_text << "\n";
    }
};

// Find the position of a closing bracket, given an opening one
int findGroup(char* text, int start) {
  int balance = 1;
  for (int i=start;text[i];i++) {
    if (text[i] == '(' && text[i-1] != '\\') {balance++;}
    else if (text[i] == ')' && text[i-1] != '\\') {balance--;}
    if (balance == 0) {
      return i;
    }
  }
  return -1;
}

// Determine an action from a string
Action* parseAction(char* text,int start,int end) {

  // Determine any modifiers
  bool isSequential = text[0] == '!';
  bool isTyping = text[0] == '>';
  if (isSequential || isTyping) {start++;}

  // iterate over the string starting at the specified beginning
  int i=start;
  while (text[i] && i<end) {
    char c = text[i];

    // Are we starting a group?
    if (c == '(' && (i == 0 || text[i-1] != '\\')) {
      int groupEnd = findGroup(text,i+1);
      if (groupEnd != -1) {
        std::cout << "Group from " << i << " to " << groupEnd << "\n";
        parseAction(text,i,groupEnd);
      }
    }else{
      // Figure out which action this corresponds to
    }

    // Increment i
    std::cout << ".";
    i++;
  }
}


int main() {
  char* test = "enter";

  parseAction(test,0,50);
}
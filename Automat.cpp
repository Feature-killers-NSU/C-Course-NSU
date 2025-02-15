#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;


//класс Конечного Автомата
class state_machine {
private:
  int m_q0;                   //начальное состояние
  int m_Q;                    //количество состояний
  set<int> m_States; // множество состояний.
  set<char> m_Sigma;          //алфавит
  set<int> m_F; //множество конечных состояний
  multimap<pair<int,char>,int> m_Delta; //функции перехода
public:
  state_machine();
  ~state_machine() = default;
 /* state_machine(string word);*/ //к доп заданию
  void determinate();
  void ident(string word) const;
  bool need_determination() const;
  state_machine(string re);
};

//ввод Конечного Автомата
state_machine::state_machine() {
  cin >> m_Q;
  cin >> m_q0;
  int F;
  cin >> F;
  for (int i = 0; i < F; i++) {
    int a;
    cin >> a;
    m_F.insert(a);
  }
  int p;
  cin >> p;
  for (int i = 0; i < p; i++) {
    int from,to;
    char value;
    cin >> from >>to; 
    cin>>value;
    m_States.insert(from);
    m_States.insert(to);
    m_Delta.insert({pair<int,char>(from,value),to});
    m_Sigma.insert(value);
  }
}

//функция возвращает новый номер состояния


//детерминация недетерминированного Конечного Автомата. Алгоритм Томпсона
void state_machine::determinate() {

  set<int> F; // новые конечные состояния
  multimap<pair<int,char>,int> delta; // новая функция перехода
  map<set<int>,int> new_states; // новые состония, которые представляют в ДКА некоторые подмн-ва состояний НКА, сопостовляются с новым номерам состояний.

  
  set<int> start_dka_state; // начальный элемент в в новом ДКА
  queue<set<int>> Queue; // Очередь для аналога широкого поиска в алг. Томпсона
  set<set<int>> Q; // куча для отсортировки, уже попадавшихся элементов

  start_dka_state.insert(m_q0); // начальный элемент инициализируем как {q_0}
  Queue.push(start_dka_state); // Добавляем в очередь в конец {q_0}
  Q.insert(start_dka_state); // Добавляем в мн-во Q,уже побывавших в Queue, {q_0}

  if (m_F.count(m_q0)==1) {
    F.insert(0);
  } // Добавление в конечные состояния F 0,если q_0 было ранее конечным
  int t=0;
  new_states[start_dka_state]=t; // номер нового начального состояния ноль
  while (!Queue.empty()) {
    
    set<int> old_dka_state = Queue.front();// выкладываем первое новое состояние в old_dka_state
    Queue.pop();//очищаем очередь от него
    
    for (auto i : m_Sigma) { //перебираем буквы алфавита 
      
      set<int> new_dka_state; //создаем следующее состояние
      for (auto j : m_Delta) { // перебираем ф-ии перехода
        if(old_dka_state.count(j.first.first) && j.first.second==i){
          new_dka_state.insert(j.second); // выбираем те отображения, q_n=delta(q_n-1,i),где q_n-1 cодержится в old_dka_state(прошлом состоянии)
          
        }
        
        
      }
      

     

      if (Q.count(new_dka_state) == 0) { // если в Queue попал в первый раз
        Queue.push(new_dka_state);
        Q.insert(new_dka_state);   // добавляем в Q
         t+=1; // добавляем +1 к номеру состояния, так как раньше оно не попадалось
        new_states[new_dka_state]=t;
        
        delta.insert({pair<int,char>(new_states[old_dka_state],i),new_states[new_dka_state]}); // вычисляем новую ф-ию перехода (сопоставляем дкшным q_n-1, i дкшное q_n).

        for (auto i : new_dka_state) { // перебираем старые нкшные состояния в новом Дка состоянии
          if (m_F.count(i) != 0) {
            F.insert(new_states[new_dka_state]); // если один из элементов был конечным, то всё дка состояние конечное
            break;
          }
        }

      } else {

       
        delta.insert({pair<int,char>(new_states[old_dka_state],i),new_states[new_dka_state]});
      }
    }
  }

  m_Q = Q.size();
  m_F = F;
  m_Delta = delta;
  m_q0 = 0;
  m_States.clear();
  for(auto j :new_states){
    m_States.insert(j.second);
  }
}

//распознает ли Конечный Автомат введенную строку?

void state_machine::ident(string word) const {
  int prtclr_moment = 0;
  for (int i = 0; i < word.length(); i++) {
    for (auto j : m_Delta) {
      if (j.first.first == prtclr_moment && j.first.second == word[i]) {
        prtclr_moment =j.second;
        break;
      }
    }
  }
  if (find(m_F.begin(),m_F.end(), prtclr_moment) != m_F.end()) {
    cout << "YES" << '\n';
  } else {
    cout << "NO" << '\n';
  }
}


bool state_machine::need_determination() const{
	for (auto i:m_States) {
    int S=0;
		for(auto j:m_Sigma){
      S+=m_Delta.count(pair<int,char>(i,j));
    
    }
    if(S!=2) return true; //детерминизация нужна
	}
	return false; //не нужна
}
state_machine::state_machine(string re) {
	m_Q = re.length();
	m_q0 = 0;
	m_F.insert(m_Q - 1);
	for (int i = 1; i < m_Q; i++) {
    m_States.insert(i-1);
		m_Sigma.insert(re[i-1]);
		m_Delta.insert({pair<int,char>(i-1,re[i-1]),i});
		
	}
        /*this->determinate();*/
        
}




int main(){
  state_machine Godel=state_machine();
  Godel.determinate();
  int N;
  cin>>N;
  for(int i=0;i<N;i++){
    string s;
    cin>>s;
    Godel.ident(s);
    }
  /*state_machine Godel=state_machine("aabc");
  Godel.ident("aabc");
  Godel.ident("aas");*/
  
}

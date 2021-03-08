#include "ll_cycle.h"

bool ll_has_cycle(node *head) {
    /* Ваш код должен быть написан только внутри этой функции */
    node* turtle = head;
    node* rabbit = head;
    
    while( rabbit != nullptr)
    {
    	if(rabbit->next == nullptr || rabbit-> next-> next == nullptr)
    	    return false;
    	
    	rabbit=rabbit->next->next;
    	
    	if(turtle == rabbit)
    	    return true;
    	   
    	turtle=turtle->next;
    }
    
    return false;
}

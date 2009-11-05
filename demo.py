import time
import os, sys
import corners

if sys.platform == 'win32':            
    def clear_screen(): 
        os.system('cls')
else:
    def clear_screen(): 
        os.system('clear')        

#def clear_screen():
#    print '---'
    
def main():    
    g = corners.Game()
    pause = 1
    small_pause = .1
    
    clear_screen()
    g.show_desk()
    
    while not g.is_gameover():        
        g.set_move_white()
        
        trace = g.best_step()         
        for pfrom, pto in zip(trace[:-1], trace[1:]):            
            g.move(pfrom, pto)
            clear_screen()
            g.show_desk()
            time.sleep(small_pause)
        time.sleep(pause)
        
        g.set_move_black()
        
        trace = g.best_step()         
        for pfrom, pto in zip(trace[:-1], trace[1:]):            
            g.move(pfrom, pto)
            clear_screen()
            g.show_desk()
            time.sleep(small_pause)
                        
        time.sleep(pause)        
        print 
        
if __name__ == '__main__':
    main()
    
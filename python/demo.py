#!/usr/bin/python
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
    small_pause = 0.1

    clear_screen()
    corners.dump_desk(g)

    def make_move():
        trace = g.best_step()
        for pfrom, pto in zip(trace[:-1], trace[1:]):
            g.move(pfrom, pto)
            clear_screen()
            corners.dump_desk(g)
            time.sleep(small_pause)
        time.sleep(pause)

    while not g.is_gameover():
        g.set_move_white()
        make_move()

        g.set_move_black()
        make_move()

if __name__ == '__main__':
    main()

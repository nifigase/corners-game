import random
try:
    from itertools import product
except ImportError:  # Python < 2.6
    import operator
    def product(*args, **kwds):
        pools = map(tuple, args) * kwds.get('repeat', 1)
        result = [[]]
        for pool in pools:
            result = [x+[y] for x in result for y in pool]
        for prod in result:
            yield tuple(prod)
    def sum(seq, start=0):
        return reduce(operator.add, seq, start)
    
def apply_offset(p, k):
    return tuple(map(operator.add, p, k))
            
class Game(object):
    desksize = 8
    spacesize = 2
    initsize = 5
    
    DEPTH = 3
    WITE_PER_LEVELS = 1.0

    def __init__(self, white=set(), black=set()):
        self.white_initial = set(p for p in product(range(self.initsize), repeat=self.spacesize) 
                                   if sum(p) < self.initsize)
        self.black_initial = set(self.reverse(p) for p in self.white_initial)
        
        self.white = white or self.white_initial
        self.black = black or self.black_initial
            
        self.white_energy = dict((p, int( 
#                + sum(p) + (self.K_IN if p in self.black_initial else self.K_FREESPASE)
#                + sum(self.reverse(p)) * (self.K_OUT if p in self.white_initial else 0)
                + sum(p) 
                + (50 if p in self.black_initial else 1)
                - (50 if p in self.white_initial else 0)
                - (100 if p == (0, 0) else 0)
                #- abs(reduce(operator.sub, p)
            )) for p in product(range(self.desksize), repeat=self.spacesize))
        self.black_energy = dict((self.reverse(p), v) for p, v in self.white_energy.items())
        
        self.set_move_white()
                
    def set_move_white(self):
        self.current_energy = self.white_energy
        self.current = self.white
        self.current_initial = self.white_initial

    def set_move_black(self):
        self.current_energy = self.black_energy
        self.current = self.black        
        self.current_initial = self.black_initial
        
    def is_gameover(self):
        return self.black == self.white_initial or self.white == self.black_initial 
        
    def reverse(self, p):
        return tuple(self.desksize - x - 1 for x in p)
    
    def is_busy(self, p):
        return p in self.white or p in self.black
    
    def is_out_of_desk(self, p):
        return not all(0 <= x < self.desksize for x in p)
    
    def is_free(self, p):
        return not self.is_busy(p) and not self.is_out_of_desk(p) 
    
    nearnabes = [k for k in product((-1, 0, 1), repeat=spacesize) if sum(map(abs, k)) == 1]
    farstep_rules = [(nabe, filter(any, [apply_offset(nabe, offset) for offset in nearnabes])) for nabe in nearnabes]
             
    def move(self, p1, p2):
        assert self.is_free(p2), '%s is not free' % str(p2)
        t = self.white if (p1 in self.white) else self.black
        t.remove(p1)
        t.add(p2)
            
    def _farsteps(self, pfrom, exclude=None):
        if exclude is None:
            exclude = set()
        exclude.add(pfrom)
        result = []
        for nabe, tos in self.farstep_rules:
            if not self.is_busy(apply_offset(pfrom, nabe)):
                continue
            for to in tos:
                to = apply_offset(pfrom, to)
                if to not in exclude and self.is_free(to):
                    result.append([to])
                    for substeps in self._farsteps(to, exclude):
                        result.append(substeps)
        return [[pfrom] + trace for trace in result]
        
    def point_steps(self, pfrom):
        traces = []
        traces += self._farsteps(pfrom)
        traces += [[pfrom, p] for p in [apply_offset(pfrom, k) for k in self.nearnabes] if self.is_free(p)]
        
        traces.sort(key=len)
        result = dict()
        for t in traces:
            key = t[0], t[-1]
            if key not in result:
                result[key] = t
        return result.values()

        #return set(simplesteps).union(self._farsteps(pfrom))

    def calculate_energy(self):
#        +get_no_steps
        blocking_wite = sum(
            -5 for p in self.current_initial
                if p in self.current
                and not self.point_steps(p))
        return sum(self.current_energy[p] for p in self.current) + blocking_wite
    
    def possible_steps(self):
        for pfrom in list(self.current):
            for trace in self.point_steps(pfrom):
                yield trace
                
    def best_step(self, level=0):
        steps = []
        for trace in self.possible_steps():
            pfrom, pto = trace[0], trace[-1]
            self.move(pfrom, pto)
            steps.append((level, self.calculate_energy(), trace))
            self.move(pto, pfrom)
        max_energy = max(energy for level, energy, trace in steps)
        return random.choice([trace for level, energy, trace in steps if energy == max_energy])

    def show_desk(self, debug=False):
        print 'BLACK' if self.current == self.black else 'WHITE'
        for row in range(self.desksize):
            for col in range(self.desksize):
                p = (row, col)
                if p in self.white:
                    print 'W',
                elif p in self.black:
                    print 'B',
                else:
                    print '.',
                if debug:
                    print '(%04d)' % self.current_energy[p],
            print 
        if debug:
            print 'energy: %d' % self.calculate_energy()

if __name__ == '__main__':
    g = Game()
    for i in range(1):
        print
        g.show_desk(True)
        trace = g.best_step()
        g.move(trace[0], trace[-1])

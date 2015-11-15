from loa_game_AnyTime import WHITE, BLACK, LinesOfActionState, SpinAction, MoveAction, DIRECTIONS, Direction
from game_agent import GameAgent
from alpha_beta_ver2 import AlphaBetaSearchAnyTimeTemp
from Hueristics import utilityes

#_________________________________________________________
class AnyTimeAlphaBetaAgent2(GameAgent):
    def move(self, game_state):
        return self.alphaBeta.search(game_state)
    
    def setup(self, player, game_state, turn_time_limit, setup_time_limit):
        self.player = player
        par=(0,1,1,0,1,2,0,0)
        u = lambda state,time,safe: utilityes().utilityAnyTime(state,self.player,par,time,safe)
        self.alphaBeta = AlphaBetaSearchAnyTimeTemp(self.player, 3, u,turn_time_limit)

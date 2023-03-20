#!/bin/python3
import random

def read_player_input():
    msg = '[r]ock, [p]aper, [s]cissor: '
    move = input(msg)
    for k,v in moves.items():
        if move == k or move == v:
            return v

# this is ugly -_-
def compare(player_move, computer_move):
    match player_move:
        case 'rock':
            match computer_move:
                case 'rock':
                    return 'tie'
                case 'paper':
                    return 'computer'
                case 'scissor':
                    return 'player'
        case 'paper':
            match computer_move:
                case 'rock':
                    return 'player'
                case 'paper':
                    return 'tie'
                case 'scissor':
                    return 'computer'
        case 'scissor':
            match computer_move:
                case 'rock':
                    return 'computer'
                case 'paper':
                    return 'player'
                case 'scissor':
                    return 'tie'


moves = {'r':'rock', 'p':'paper', 's':'scissor'}

player_move = read_player_input()
computer_move = random.choice(list(moves.values()))
result = compare(player_move, computer_move)

print(f'(player){player_move} VS (computer){computer_move} !!')

match result:
    case "player":
        print("player won!!")
    case "computer":
        print("computer won!!")
    case "tie":
        print("it's a tie!!")

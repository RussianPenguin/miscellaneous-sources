# -*- encoding: utf-8 -*- from __future__ import unicode_literals

def transpose(board):
	transpose = [[board[y][x] for y in range(len(board))] for x in range(len(board))]
	return transpose
		

def suggest_num(num, board):
	suggest_board = [[board[x][y] for y in range(len(board))] for x in range(len(board))]
	#print 'num', num

	for x in range(3):
		for y in range(3):
			can_be_placed = True

			# проверяем клетку 3x3 на позможность записать туда num
			for inner_x in range(3):
				for inner_y in range(3):
					if board[x*3 + inner_x][y*3 + inner_y] == num:
						can_be_placed = False
			if not can_be_placed:
				continue

			# заполняем num все места, где он может появиться
			for inner_x in range(3):
				for inner_y in range(3):
					if not board[x*3 + inner_x][y*3 + inner_y] == 0:
						continue

					can_be_placed = True

					for scan in range(9):
						if board[x*3 + inner_x][scan] == num:
							can_be_placed = False
					for scan in range(9):
						if board[scan][y*3 + inner_y] == num:
							can_be_placed = False

					if can_be_placed:
						suggest_board[x*3 + inner_x][y*3 + inner_y] = num

	#print_board(suggest_board)
	for x in range(3):
		for y in range(3):
			# ищем особые ситуации. это когда в клетке 3х3 num расположен только в строке/столбце
			lines = []
			rows = []

			for inner_x in range(3):
				for scan in range(3):
					if suggest_board[x*3 + inner_x][y*3 + scan] == num and not inner_x in lines:
						lines.append(inner_x)
				
			for inner_y in range(3):
				for scan in range(3):
					if suggest_board[x*3 + scan][y*3 + inner_y] == num and not inner_y in rows:
						rows.append(inner_y)

			# Если в клетке 3х3 искомым num зпполнена только одна строка или столбец, 
			#  то в других клетках эта строка/стоблец будет свободна от num
			if len(lines) == 1:
				for y_for_clear in range(3):
					if y_for_clear == y:
						continue

					for scan in range(3):
						if suggest_board[x*3 + lines[0]][y_for_clear*3 + scan] == num:
							suggest_board[x*3 + lines[0]][y_for_clear*3 + scan] = 0

			if len(rows) == 1:
				for x_for_clear in range(3):
					if x_for_clear == x:
						continue

					for scan in range(3):
						if suggest_board[x_for_clear*3 + scan][y*3 + rows[0]] == num:
							suggest_board[x_for_clear*3 + scan][y*3 + rows[0]] = 0
											
	#print_board(suggest_board)
	return suggest_board

def describe(suggests):
	description = []

	for x in range(3):
		for y in range(3):
			unique = {}
			stop_num = []
			# ишем подсказки, которые содержат только одно число
			for inner_x in range(3):
				for inner_y in range(3):
					idx = x*3 + inner_x, y*3+inner_y
					elem = suggests[idx[0]][idx[1]]

					if type(suggests[x*3 + inner_x][y*3+inner_y]) != list:
						continue

					if len(suggests[x*3 + inner_x][y*3+inner_y]) == 1:
						if elem[0] in unique:
							stop_num.append(elem[0])
						else:
							unique[elem[0]] = idx

			for num in unique:
				if not num in stop_num:
					description.append((unique[num], num))
			
			# теперь нужно найти номера, которые встречаются только в одном блоке из 9 максимум (на малом квадрате)
			# сломарик num: idx
			unique = {}
			# значения, которые встретились повторно
			stop_num = []

			for inner_x in range(3):
				for inner_y in range(3):
					idx = x*3 + inner_x, y*3+inner_y
					elem = suggests[idx[0]][idx[1]]

					if type(elem) != list:
						continue

					for scan in range(len(elem)):
						#print 'scan suggest element', scan, elem[scan]
						if elem[scan] in unique:
							stop_num.append(elem[scan])
						else:
							unique[elem[scan]] = idx
			#print 'description', unique, stop_num
			for num in unique:
				if not num in stop_num:
					description.append((unique[num], num))
			
	return description

def suggest(board):
	suggests = [[board[x][y] if board[x][y] != 0 else [] for y in range(len(board))] for x in range(len(board))]
	#print_board(suggests)
	for x in xrange(1, 10):
		suggest_for_num = suggest_num(x, board);
		for line in range(9):
			for row in range(9):
				if type(suggests[line][row]) == list:
					suggest_item = suggest_for_num[line][row]
					if suggest_item != 0 and not suggest_item in suggests[line][row]:
						suggests[line][row].append(suggest_item)
	print 'suggest for board'
	print_board(suggests)
	print 'description'
	desc = describe(suggests)
	print desc
	print "\n"
	return desc
		
def is_complete(board):
	for x in range(9):
		for y in range(9):
			if board[x][y] == 0:
				return False
	return True	
	

def print_board(board):
	for x in board:
		print x

if __name__ == '__main__':
	board = [map(int, raw_input().split()) for _ in range(9)]

	while not is_complete(board):
		print 'matrix before scan'
		print_board(board)
		suggest_data = suggest(board)
		if not len(suggest_data):
			print "Sorry. couldn't solve this"
			break

		for item in suggest_data:
			idx = item[0]
			board[idx[0]][idx[1]] = item[1]
		print 'matrix after iteration'
		print_board(board)

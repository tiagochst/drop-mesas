import random
from random import randrange

x_str = '__________          ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'

x_list = []
for i in x_str:
	x_list.append(i)
random.shuffle(x_list);

x = ''
for i in x_list:
	x = x+i

def randomName(N):
	a = randrange(0, len(x)-2)
	b = randrange(a+1, min(len(x)-1, a+N))
	return x[a:b]

def randomDate():
	return randrange(10000000, 99999999)

def geraEspec(nEspec):
	print nEspec

	for i in xrange(0, nEspec):
		nomeP = randomName(30)
		nomeC = randomName(30)
		caminho = randomName(255)
		descricao = randomName(500)
		data = randomDate()
		print '%(id)d|%(C)s|%(P)s|%(cam)s|%(data)d|%(descr)s' % {'id':i, 'C':nomeC, 'P':nomeP, 'cam':caminho, 'data':data, 'descr':descricao}

def geraIndiv(nIndiv, nEspec):
	print nIndiv

	for i in xrange(0, nIndiv):
		idE = randrange(0, nEspec)
		if randrange(0, 2) == 0: sexo = 'M'
		else: sexo = 'F'
		print '%(idE)d|%(id)d|%(sexo)c' % {'id':i, 'idE':idE, 'sexo':sexo}

def geraCaptu(nCaptu, nIndiv):
	print nCaptu

	for i in xrange(0, nCaptu):
		idI = randrange(0, nIndiv)
		local = randomName(50)
		data = randomDate()
		larg = randrange(10, 100)
		compr = randrange(10, 100)
		peso = randrange(70, 300)
		print '%(idI)d|%(compr)s|%(larg)s|%(peso)s|%(data)d|%(local)s' % {'idI':idI, 'compr':compr, 'larg':larg, 'peso':peso, 'data':data, 'local':local}


nEspec = 100
nIndiv = 100
nCaptu = 100

#geraEspec(nEspec)
geraIndiv(nIndiv, nEspec)
#geraCaptu(nCaptu, nIndiv)


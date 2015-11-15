from scipy.stats.stats import ttest_ind
from random import Random
from matplotlib.pyplot import scatter, show, plot, subplot, axis, xlabel, ylabel,\
    title, subplots_adjust, legend

def average(s):
    return float(sum(s)) / len(s)

rnd = Random(17)

num_tosses = 200

# These require a more tosses for the difference to be significant.
#p1 = rnd.uniform(0.8, 0.9)
#p2 = rnd.uniform(0.8, 0.9)
p1 = 0.8
p2 = 0.9

s1 = []
s2 = []
for i in xrange(0, num_tosses+1):
    if rnd.random() < p1:
        s1 += [1]
    else:
        s1 += [0]
    
    if rnd.random() < p2:
        s2 += [1]
    else:
        s2 += [0]

a1 = []
a2 = []
for i in xrange(0, num_tosses+1):
    a1 += [ average( s1[ : (i+1)] ) ]
    a2 += [ average( s2[ : (i+1)] ) ]

ps = []
for i in xrange(0, num_tosses+1):
    statistic, p = ttest_ind(s1[ : i+1], s2[ : i+1])
    ps += [p]

subplot(211)
line1 = plot(range(0, num_tosses+1), a1, color='blue')
line2 = plot(range(0, num_tosses+1), a2, color='black')
legend((line1, line2), ('p1', 'p2'))
axis([0, num_tosses, 0, 1])
xlabel('Number of tosses')
ylabel('Average heads')
title('Estimated probability of heads')

subplot(212)
pline = plot(range(0, num_tosses+1), ps, color='green')
threshold = plot(range(0, num_tosses+1), [0.05] * (num_tosses+1), color='red')
legend((pline, threshold), ('ttest', '0.05 threshold'))
axis([0, num_tosses, 0, 1])
xlabel('Number of tosses')
ylabel('p-value')
title('Probability of wrongfully rejecting p1=p2')

subplots_adjust(hspace=0.5)

show()
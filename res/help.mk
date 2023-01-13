define _usage
cat << 'EOF'
Miller Rabin Test

Given an odd number n > 2 we want to check if n might be prime.
Therefor we test a witness a so that
n = 2^m * d + 1
Where we will check if a^d = `1 mod n`

Attention: If a single witness is not +/-1, then n is
guaranteed to not be prime. But if all are +/-1, then
n has a 1/(4^k) chance to be prime where k is the number
of witnesses used for proove.

Call:
<++> [OPTIONS] -t n (-s a | -l a,b,c,... | -S s) 

OPTIONS:
	-v | --verbose
		Be very talkative
	-o | --outStream
		Log to stream of file, default is stdout

Mandatory:
	-t | --test n
		Test if n is a prime number
Mutual but mandatory choices:
	-s | --single a
		Check a single Witness number a
	-l | --list [NUMBERS]
		Take all the numbers that will come after this
		argument. If provided it must be the very last argument
	-S | --special SET
		Check n against a Set of special witnesses.
		SET: will {} guarantees all odd for n < _ _
			0 => Test a = {2;3} 										
								n < _000,000,000,000,000,001,373,653_								
			1 => Test a = {31;73}
								n < _000,000,000,000,000,009,080,191_
			2 => Test a = {2;3;5}
								n < _000,000,000,000,000,025,326,001_
			3 => Test a = {2;13;23;1,662,803}
								n < _000,000,000,001,122,004,669,633_
			4 => Test a = {2;3;5;7;11}
								n < _000,000,000,002,152,302,898,747_
			5 => Test a = {2;3;5;7;11;13;17;19;23;29;31;37}
			LIMIT:		n < _000,018,446,744,073,709,551,616_
			REALLY:		n < _318,665,857,834,031,151,167,461_

EOF
endef
export usage=$(value _usage)

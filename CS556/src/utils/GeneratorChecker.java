package utils;

import java.math.BigInteger;

public class GeneratorChecker {

	private BigInteger prime;

	private BigInteger counter;

	public GeneratorChecker(BigInteger prime) {
		this.prime = prime;
		this.counter = new BigInteger("2");
	}

	public BigInteger nextGenerator() {
		while (true) {
			if (testGenerator(counter, prime))
				break;
			counter = counter.add(BigInteger.ONE);
		}
		BigInteger ret = counter;
		counter = counter.add(BigInteger.ONE);
		return ret;
	}

	private boolean testGenerator(BigInteger value, BigInteger prime) {
		BigInteger start = BigInteger.ONE;
		while (start.compareTo(prime) < 0) {
			System.out.println(value.modPow(start, prime));
			if (value.modPow(start, prime).equals(BigInteger.ONE)) {
				if (start.equals(prime.subtract(BigInteger.ONE))) {
					return true;
				}
				return false;
			}
			start = start.add(BigInteger.ONE);
		}
		return false;
	}

	public static void main(String[] args) {
//		System.out.println(new GeneratorChecker(new BigInteger("227"))
//				.nextGenerator());
		
		System.out.println(new BigInteger("116").modPow(new BigInteger("8"), new BigInteger("227")));
	}
}

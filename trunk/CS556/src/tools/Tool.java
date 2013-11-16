package tools;

import java.math.BigInteger;


public class Tool {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		BigInteger a = new BigInteger("116");
		BigInteger e = new BigInteger("8");
		BigInteger p = new BigInteger("227");
		
		System.out.println(a.modPow(e, p));
	}

}

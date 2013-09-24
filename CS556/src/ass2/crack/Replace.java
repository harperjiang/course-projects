package ass2.crack;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import utils.OneOneDictionary;

public class Replace {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(
				new FileInputStream("src/ass2/crack/translate")));
		String line = br.readLine();
		br.close();

		// HssiOUVeUt
		// assignment
		// imLlementatiNn
		// implementation
		// pJogJamming
		// programming
		// langdage
		// language
		// anK
		// any
		// AryptographyR
		// cryptography
		// hhoiheR
		// choice
		// gBa
		// rsa
		// numiersR
		// number
		// probide
		// provide
		// tane
		// take
		// X\]^
		// 2013
		OneOneDictionary dict = new OneOneDictionary(new char[][] {
				{ 'M', 't' }, { 'Q', 'h' }, { 'W', 'e' }, { 'I', ' ' },
				{ 'm', 'x' }, { 'f', 'f' }, { 'T', 'i' }, { '[', 'l' },
				{ 'S', 's' }, { 'H', 'A' }, { 'O', 'g' }, { 'U', 'n' },
				{ 'V', 'm' }, { 'P', 'a' }, { 'N', 'o' }, { 'L', 'p' },
				{ 'J', 'r' }, { 'd', 'u' }, { 'K', 'y' }, { 'A', 'C' },
				{ 'h', 'c' }, { 'c', 'd' }, { 'g', 'R' }, { 'B', 'S' },
				{ 'e', 'w' }, { 'i', 'b' }, { 'j', '-' }, { 'R', '.' },
				{ '`', '\n' }, { 'b', 'v' }, { 'G', 'M' }, { 'C', '4' },
				{ 'D', '5' }, { 'E', '6' }, { 'F', '/' }, { 'Z', 'F' },
				{ 'k', 'Y' }, { 'n', 'k' }, { 'l', 'I' }, { 'p', 'T' },
				{ 'a', ',' }, { 'o', ':' }, { 'X', '2' }, { '\\', '0' },
				{ ']', '1' }, { '^', '3' }, { 'Y', '(' }, { '_', ')' } });
		PrintWriter pw = new PrintWriter(new FileOutputStream(
				"src/ass2/crack/output"));
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < line.length() - 1; i++)
			sb.append(dict.lookup(line.charAt(i)));
		pw.println(sb.toString());
		pw.close();
	}
}

package tools;


public class Tool {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int num = 4567;
		for(int i = 2 ; i < num;i++) {
			if(num%i == 0)
				System.out.println(i);
		}
	}

}

package dns;

import java.util.HashMap;
import java.util.Map;

import org.xbill.DNS.Lookup;
import org.xbill.DNS.Name;
import org.xbill.DNS.Record;
import org.xbill.DNS.Type;

public class LookupDemo {

	static Map<String, Record> resultMap = new HashMap<String, Record>();

	public static void recordAnswer(String name, Lookup lookup) {
		System.out.println(name);
		int result = lookup.getResult();
		if (result != Lookup.SUCCESSFUL)
			System.out.print(" " + lookup.getErrorString());

		Name[] aliases = lookup.getAliases();
		if (aliases.length > 0) {
			System.out.print("# aliases: ");
			for (int i = 0; i < aliases.length; i++) {
				System.out.print(aliases[i]);
				if (i < aliases.length - 1)
					System.out.print(" ");
			}
			System.out.println();
		}
		if (lookup.getResult() == Lookup.SUCCESSFUL) {
			Record[] answers = lookup.getAnswers();
			for (int i = 0; i < answers.length; i++)
				// resultMap.put(((ARecord) answers[i]).getAddress()
				// .getHostAddress(), answers[i]);
				System.out.println(answers[i]);
		}
	}

	public static void main(String[] args) throws Exception {
		int type = Type.A;
		String domainName = "www.twitter.com";
		for (int i = 0; i < 1; i++) {
			Thread.sleep(200);
			Lookup l = new Lookup(domainName, type);
			l.run();
			recordAnswer(domainName, l);
		}
	}

}

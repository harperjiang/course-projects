package common.model;


public class PredicateHelper {

	public static Predicate singleOne(String... varNames) {
		Variable[] vars = new Variable[varNames.length];
		for (int i = 0; i < vars.length; i++) {
			vars[i] = new Variable(varNames[i]);
		}
		Predicate atLeastOneOne = new Predicate(Operator.OR, vars);

		Predicate[] interact = new Predicate[varNames.length
				* (varNames.length - 1) / 2];
		int count = 0;
		for (int i = 0; i < varNames.length; i++) {
			for (int j = i + 1; j < varNames.length; j++) {
				interact[count++] = new Predicate(Operator.AND, new Variable(
						varNames[i]), new Variable(varNames[j]));
			}
		}
		Predicate atMostOneOne = new Predicate(Operator.NOT, new Predicate(
				Operator.OR, interact));

		return new Predicate(Operator.AND, atLeastOneOne, atMostOneOne);
	}
}

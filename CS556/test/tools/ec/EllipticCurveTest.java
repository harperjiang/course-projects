package tools.ec;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.math.BigInteger;

import org.junit.Test;

import tools.ec.EllipticCurve.Element;

public class EllipticCurveTest {

	@Test
	public void testCalculate() {
		EllipticCurve ec = new EllipticCurve(new BigInteger("43"),
				new BigInteger("4"), new BigInteger("34"));
		assertEquals(new BigInteger("41").pow(2).mod(new BigInteger("43")),
				ec.calculate(new BigInteger("12")));
	}

	@Test
	public void testElementEquals() {
		EllipticCurve ec = new EllipticCurve(new BigInteger("43"),
				new BigInteger("4"), new BigInteger("34"));
		Element element1 = new Element(ec, new BigInteger("12"),
				new BigInteger("41"));
		Element element2 = new Element(ec, new BigInteger("12"),
				new BigInteger("41"));
		Element element3 = EllipticCurve.ZERO;
		Element element4 = EllipticCurve.ZERO;

		assertEquals(element1, element2);
		assertTrue(!element2.equals(element3));
		assertEquals(element3, element4);
	}

	@Test
	public void testMul() {
		EllipticCurve ec = new EllipticCurve(new BigInteger("43"),
				new BigInteger("4"), new BigInteger("34"));
		Element element1 = new Element(ec, new BigInteger("12"),
				new BigInteger("41"));

		assertEquals(element1, element1.mul(1));
		assertEquals(
				element1.add(element1).add(element1).add(element1)
						.add(element1), element1.mul(5));
		assertEquals(element1.mul(4), new Element(ec, new BigInteger("31"),
				new BigInteger("8")));
	}

	@Test
	public void testBigMul() {
		EllipticCurve curve = new EllipticCurve(new BigInteger(
				"231980187997634794246138521723892165531"), new BigInteger(
				"286458106491124997002528249079664631375"), new BigInteger(
				"300957219209219074658154646971415184777"));
		Element g = new Element(curve, new BigInteger(
				"147686244687917713362777524310538490730"), new BigInteger(
				"83517868646140609087900046649718421315"));
		for (int i = 1; i < 100000; i++) {
			Element m1 = g.mul(i);
			Element m2 = g.mul(new BigInteger(String.valueOf(i)));
			assertEquals(m1, m2);
		}
	}

	@Test
	public void testMulResult() {
		EllipticCurve curve = new EllipticCurve(new BigInteger(
				"231980187997634794246138521723892165531"), new BigInteger(
				"286458106491124997002528249079664631375"), new BigInteger(
				"300957219209219074658154646971415184777"));
		Element g = new Element(curve, new BigInteger(
				"147686244687917713362777524310538490730"), new BigInteger(
				"83517868646140609087900046649718421315"));
		Element a = g.mul((710000000l - 1) * 6l + (5 + 1));
		System.out.println(a);
	}

	@Test
	public void testToString() {
		EllipticCurve ec = new EllipticCurve(new BigInteger("43"),
				new BigInteger("4"), new BigInteger("34"));
		assertEquals("(31,8)", new Element(ec, new BigInteger("31"),
				new BigInteger("8")).toString());
		EllipticCurve curve = new EllipticCurve(new BigInteger(
				"231980187997634794246138521723892165531"), new BigInteger(
				"286458106491124997002528249079664631375"), new BigInteger(
				"300957219209219074658154646971415184777"));
		Element g = new Element(curve, new BigInteger(
				"147686244687917713362777524310538490730"), new BigInteger(
				"83517868646140609087900046649718421315"));

		assertEquals(
				"(147686244687917713362777524310538490730,83517868646140609087900046649718421315)",
				g.toString());
	}

	@Test
	public void testBigEC() throws Exception {
		EllipticCurve curve = new EllipticCurve(new BigInteger(
				"231980187997634794246138521723892165531"), new BigInteger(
				"286458106491124997002528249079664631375"), new BigInteger(
				"300957219209219074658154646971415184777"));

		Element g = new Element(curve, new BigInteger(
				"147686244687917713362777524310538490730"), new BigInteger(
				"83517868646140609087900046649718421315"));

		Element t2res = new Element(curve, new BigInteger(
				"185679744865995170675005329508022006340"), new BigInteger(
				"125045516627717935060014878508379857578"));
		Element t1res = new Element(curve, new BigInteger(
				"43262117017202663893621243610099313102"), new BigInteger(
				"142776932818164584346145156422724989496"));
		Element t3res = new Element(curve, new BigInteger(
				"181922298841509047673190645107910297274"), new BigInteger(
				"79358194521502018591922659866811702362"));
		Element t5res = new Element(curve, new BigInteger(
				"172642072769504024938410998726795773279"), new BigInteger(
				"142775406483569814332409984744152345058"));
		Element t0res = new Element(curve, new BigInteger(
				"97206581188579212201718128813316986842"), new BigInteger(
				"141908870349872928153727978432644561396"));
		Element t4res = new Element(curve, new BigInteger(
				"50927023185068585849855514811922933061"), new BigInteger(
				"157049452050332603844593228868232663226"));
		assertEquals(t1res, t0res.add(g));
		assertEquals(t2res, t1res.add(g));
		assertEquals(t3res, t2res.add(g));
		assertEquals(t4res, t3res.add(g));
		assertEquals(t5res, t4res.add(g));

		Element t2res1 = new Element(curve, new BigInteger(
				"157459826255143223496479897432029094819"), new BigInteger(
				"7402159039590975840017914789047017362"));
		Element t1res1 = new Element(curve, new BigInteger(
				"184337645654899486849774073095937299413"), new BigInteger(
				"91008407626475074143675756200449292226"));
		Element t3res1 = new Element(curve, new BigInteger(
				"80863830894169111106213107279535973333"), new BigInteger(
				"198836499966585774792771771393581483827"));
		Element t0res1 = new Element(curve, new BigInteger(
				"139131029713445534618275120048460216898"), new BigInteger(
				"149631398023625218899212947486725863341"));
		Element t4res1 = new Element(curve, new BigInteger(
				"144148059068889137470264422648679951273"), new BigInteger(
				"6504875881032848207736225367723478186"));
		Element t5res1 = new Element(curve, new BigInteger(
				"149869352923364030258679597953132007012"), new BigInteger(
				"131179991092517156716600005722105412074"));

		assertEquals(t1res1, t0res1.add(g));
		assertEquals(t2res1, t1res1.add(g));
		assertEquals(t3res1, t2res1.add(g));
		assertEquals(t4res1, t3res1.add(g));
		assertEquals(t5res1, t4res1.add(g));

		Element t2res2 = new Element(curve, new BigInteger(
				"123785648622435895459084104177481224038"), new BigInteger(
				"112725517149650088559527649338032787664"));
		Element t3res2 = new Element(curve, new BigInteger(
				"181505483281047337707654281889008765179"), new BigInteger(
				"58567913062220599979611363229196038320"));
		Element t1res2 = new Element(curve, new BigInteger(
				"68953731515686487846904482275087444900"), new BigInteger(
				"194432678596794109527094213377518044693"));
		Element t0res2 = new Element(curve, new BigInteger(
				"102088946538444628755820073788353875305"), new BigInteger(
				"84900080699227056771819002147855634558"));
		Element t4res2 = new Element(curve, new BigInteger(
				"105967216914165728040404182073232527865"), new BigInteger(
				"139141907865102336669814144507371505609"));
		Element t5res2 = new Element(curve, new BigInteger(
				"118996407207663787057944489875932504651"), new BigInteger(
				"73426927219965812825803273705664218122"));

		assertEquals(t1res2, t0res2.add(g));
		assertEquals(t2res2, t1res2.add(g));
		assertEquals(t3res2, t2res2.add(g));
		assertEquals(t4res2, t3res2.add(g));
		assertEquals(t5res2, t4res2.add(g));

		Element t2r1 = new Element(curve, new BigInteger(
				"185679744865995170675005329508022006340"), new BigInteger(
				"125045516627717935060014878508379857578"));
		Element t2r2 = new Element(curve, new BigInteger(
				"180482765896097312024853339780066405481"), new BigInteger(
				"220597258752117042214140250938328172780"));
		Element t2r3 = new Element(curve, new BigInteger(
				"230236337248457036954505712025559288380"), new BigInteger(
				"30624279819461208453756283208409961711"));
		Element t0r1 = new Element(curve, new BigInteger(
				"97206581188579212201718128813316986842"), new BigInteger(
				"141908870349872928153727978432644561396"));

		assertEquals(t2r1, t0r1.add(g.mul(2)));
	}

	@Test
	public void testBigECInterval() {
		EllipticCurve curve = new EllipticCurve(new BigInteger(
				"231980187997634794246138521723892165531"), new BigInteger(
				"286458106491124997002528249079664631375"), new BigInteger(
				"300957219209219074658154646971415184777"));

		Element g = new Element(curve, new BigInteger(
				"147686244687917713362777524310538490730"), new BigInteger(
				"83517868646140609087900046649718421315"));

		Element t2r1 = new Element(curve, new BigInteger(
				"185679744865995170675005329508022006340"), new BigInteger(
				"125045516627717935060014878508379857578"));
		Element t2r2 = new Element(curve, new BigInteger(
				"180482765896097312024853339780066405481"), new BigInteger(
				"220597258752117042214140250938328172780"));
		Element t2r3 = new Element(curve, new BigInteger(
				"230236337248457036954505712025559288380"), new BigInteger(
				"30624279819461208453756283208409961711"));
		Element t0r1 = new Element(curve, new BigInteger(
				"97206581188579212201718128813316986842"), new BigInteger(
				"141908870349872928153727978432644561396"));
		Element t0r2 = new Element(curve, new BigInteger(
				"126619164277821060853358933323435416364"), new BigInteger(
				"158108872031274340029916308842712637005"));
		Element t0r3 = new Element(curve, new BigInteger(
				"26550239180045455594694623779508678525"), new BigInteger(
				"185664451527367018435963884961820825349"));

		assertEquals(g.mul(2), t2r1.add(t0r1.negate()));
		assertEquals(t2r1, g.mul(2).add(t0r1));
		assertEquals(t0r1.add(g.mul(5)), t2r2.add(t2r1.negate()));
		assertEquals(t0r1.add(g.mul(5)), t2r3.add(t2r2.negate()));
		assertEquals(t0r1.add(g.mul(5)), t0r2.add(t0r1.negate()));
		assertEquals(t0r1.add(g.mul(5)), t0r3.add(t0r2.negate()));
	}
}

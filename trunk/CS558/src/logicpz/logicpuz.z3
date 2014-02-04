(declare-datatypes () ((Camera Canon Casio Kodak Polaroid)))
(declare-datatypes () ((Name Adam Audrey Cynthia Kassandra)))
(declare-datatypes () ((Browser IE Firefox Opera Safari)))

(declare-fun NC(Name) Camera)
(declare-fun CN(Camera) Name)
(declare-fun NB(Name) Browser)
(declare-fun BN(Browser) Name)
(declare-fun NM(Name) Int)
(declare-fun MN(Int) Name)

(declare-var a Name)
(declare-var b Name)
(declare-var c Name)
(declare-var d Name)
(declare-const camera Camera)
(declare-const browser Browser)

(assert (forall ((name Name)) (= (CN (NC name)) name)))
(assert (forall ((name Name)) (= (BN (NB name)) name)))
(assert (forall ((name Name)) (= (MN (NM name)) name)))

(assert (forall ((name Name)) (and (<= (NM name) 4) (>= (NM name) 1))))

;1. Of Audrey and the photographer with the Canon camera, one only uses Safari for their web surfing and the other has the 4.0 megapixel camera.
(assert (or (and (= (NB (CN Canon)) Safari) (= (NM Audrey) 3)) (and (= (NM (CN Canon)) 3) (= (NB Audrey) Safari))))
;2. The photographer with the Kodak camera is Cynthia.
(assert (= (NC Cynthia) Kodak))
;3. The person with the 4.0 megapixel camera can't stand using the Internet Explorer browser.
(assert (not (= IE (NB (MN 3)))))
;4. The person who prefers using the Internet Explorer browser has a camera with more megapixels than the photographer with the Polaroid camera.
(assert (> (NM (BN IE)) (NM (CN Polaroid))))
;5. Either the photographer with the Kodak camera or the photographer with the Polaroid camera only uses Firefox for their web surfing.
(assert (or (= Firefox (NB (CN Kodak))) (= Firefox (NB (CN Polaroid)))))
;6. The person with the 1.8 megapixel camera is Cynthia.
(assert (= 1 (NM Cynthia)))
;7. The person who prefers using the Internet Explorer browser is not Kassandra.
(assert (not (= IE (NB Kassandra))))
;8. The person who prefers using the Safari browser is Audrey.
(assert (= Safari (NB Audrey)))
;9. The photographer with the Canon camera has a camera with more megapixels than Audrey
(assert (> (NM (CN Canon)) (NM Audrey)))

(check-sat)
(get-model)
(declare-var c Int)
(declare-var l Int)
(declare-var a Int)
(declare-var r Int)
(declare-var k Int)
(declare-var s Int)
(declare-var o Int)
(declare-var n Int)

(declare-var carry1 Int)
(declare-var carry2 Int)
(declare-var carry3 Int)
(declare-var carry4 Int)

(assert (and (>= c 0) (<= c 9)))
(assert (and (>= l 0) (<= l 9)))
(assert (and (>= a 0) (<= a 9)))
(assert (and (>= r 0) (<= r 9)))
(assert (and (>= k 0) (<= k 9)))
(assert (and (>= s 0) (<= s 9)))
(assert (and (>= o 0) (<= o 9)))
(assert (and (>= n 0) (<= n 9)))

(assert (or (= carry1 0) (= carry1 1)))
(assert (or (= carry2 0) (= carry2 1)))
(assert (or (= carry3 0) (= carry3 1)))
(assert (or (= carry4 0) (= carry4 1)))

(assert (not (= c l)))
(assert (not (= c a)))
(assert (not (= c r)))
(assert (not (= c k)))
(assert (not (= c s)))
(assert (not (= c o)))
(assert (not (= c n)))

(assert (not (= l a)))
(assert (not (= l r)))
(assert (not (= l k)))
(assert (not (= l s)))
(assert (not (= l o)))
(assert (not (= l n)))

(assert (not (= a r)))
(assert (not (= a k)))
(assert (not (= a s)))
(assert (not (= a o)))
(assert (not (= a n)))

(assert (not (= r k)))
(assert (not (= r s)))
(assert (not (= r o)))
(assert (not (= r n)))

(assert (not (= k s)))
(assert (not (= k o)))
(assert (not (= k n)))

(assert (not (= s o)))
(assert (not (= s n)))

(assert (not (= o n)))

; clar
;+kson
;class
(assert (= (+ s (* carry1 10)) (+ r n)))
(assert (= (+ s (* carry2 10)) (+ (+ a o) carry1)))
(assert (= (+ a (* carry3 10)) (+ (+ l s) carry2)))
(assert (= (+ l (* carry4 10)) (+ (+ c k) carry3)))
(assert (= c carry4))
(assert (not (= c 0)))

(check-sat)
(get-model)

(assert (not (and (= n 7) (= c 1) (= k 9) (= o 8) (= r 5) (= l 0) (= a 3) (= s 2))))

(check-sat)
(get-model)


(assert (not (and (= s 2) (= a 3) (= l 0) (= n 5) (= k 9) (= c 1) (= o 8) (= r 7))))

(check-sat)
(get-model)


(assert (not (and (= s 3) (= a 4) (= l 0) (= n 6) (= k 9) (= c 1) (= o 8) (= r 7))))

(check-sat)
(get-model)

(assert (not (and (= s 3) (= a 4) (= l 0) (= n 7) (= k 9) (= c 1) (= o 8) (= r 6))))

(check-sat)
(get-model)
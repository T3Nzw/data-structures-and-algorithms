#lang racket

; рандом имплементация на опашка с два стека на racket (scheme).
; списъците в racket са едносвързани и cons добавя елемент винаги
; в началото на списъка, така че можем да симулираме стек чрез списък.
; стори ми се интересно, така че го качвам, въпреки че не е C++ :D

(define empty-queue '(() ()))

(define (singleton x) (list '() (list x)))

; това е помощна функция. по принцип не бихме искали
; да предоставяме на потребителя функция, която би нарушила
; инвариантите на структурата от данни, а именно -
; всяка непразна опашка съдържа >= 1 елемент във втория си стек
(define (mk-queue s1 s2) (list s1 s2))

(define fst-stack car)

(define snd-stack (λ (q) (car (cdr q))))

(define empty? (λ (q) (and (null? (fst-stack q)) (null? (snd-stack q)))))

(define (size q) (+ (length (fst-stack q)) (length (snd-stack q))))

(define (reverse-queue q)
  (define fst (fst-stack q))
  (define snd (snd-stack q))
  (if (null? snd)
      (mk-queue '() (reverse fst))
      q))

(define (enqueue x q)
  (define fst (fst-stack q))
  (define snd (snd-stack q))
  (if (empty? q)
      (singleton x)
      (mk-queue (cons x fst) snd)))

(define (front q)
  (if (empty? q)
      'empty-queue-error
      (car (snd-stack q))))

(define (dequeue q)
  (define fst (fst-stack q))
  ; това е един готин начин за "лениво" оценяване на локални дефиниции,
  ; които биха довели до грешка в конкретни ситуации (ако empty? q = #t).
  ; rm-front е 0-местна процедура, а оттам - специална форма (т.к. е λ-функция),
  ; която се оценява едва при извикването си, т.е. (rm-front)
  (define (rm-front) (cdr (snd-stack q)))
  (if (empty? q)
      'empty-queue-error
      (reverse-queue (mk-queue fst (rm-front)))))

(define q1 (singleton 1))

(define q2 (enqueue 2 q1))

(define (my-foldl op nv l)
  (if (null? l)
      nv
      (my-foldl op (op nv (car l)) (cdr l))))

(define (va-enqueue q . xs)
  (my-foldl (λ (xs x) (enqueue x xs)) q xs))

(define q3 (va-enqueue empty-queue 1 2 3 4 5 6 7 8 9 10))

(define (dequeue-n n q)
  (cond ((empty? q) q)
        ((<= n 0) q)
        (else (dequeue-n (- n 1) (dequeue q)))))

(define (front-n n q)
  (cond ((empty? q) '())
        ((<= n 0) '())
        (else (cons (front q) (front-n (- n 1) (dequeue q))))))

(define (snoc x l)
  (if (null? l)
      (list x)
      (cons (car l) (snoc x (cdr l)))))

; front-n + dequeue-n
; (car (split-n n q)) = (front-n q)
; (car (cdr (split-n n q))) = (dequeue-n q)
(define (split-n n q)
  (define (split-n-helper acc n q)
    (cond ((empty? q) (list acc q))
          ((<= n 0) (list acc q))
          (else (split-n-helper (snoc (front q) acc) (- n 1) (dequeue q)))))
  (split-n-helper '() n q))

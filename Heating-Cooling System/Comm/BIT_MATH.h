/*
 * BIT_MATH.h
 *
 * Created: 8/12/2023 5:17:03 PM
 *  Author: abdel
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(REG,BIT)	(REG |= (1<<BIT))
#define CLR_BIT(REG,BIT)	(REG &=~ (1<<BIT))
#define Toggle_BIT(REG,BIT) (REG ^= (1<<BIT))
#define GET_BIT(REG,BIT)	((REG >> BIT) & (0X01))
#define IS_SET(REG,BIT)		REG&(1<<BIT)>>BIT
#define IS_CLR(REG,BIT)		!(REG&(1<<BIT)>>BIT)


#endif /* BIT_MATH_H_ */
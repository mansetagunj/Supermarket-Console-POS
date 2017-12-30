#pragma once


class Offers		//Class Offers
{
public:				//Public members of Offers
	Offers() {}
	unsigned getOfferId();
	unsigned getOfferDisc();
	void setOfferId(unsigned);
	void setOfferDisc(unsigned);

private:			//Private members of Offers
	unsigned offerId;
	unsigned offerDisc;
};
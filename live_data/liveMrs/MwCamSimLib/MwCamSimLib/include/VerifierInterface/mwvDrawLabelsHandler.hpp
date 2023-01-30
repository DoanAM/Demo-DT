// (C) 2013-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVDRAWLABELSHANDLER_HPP_
#define MW_MWVDRAWLABELSHANDLER_HPP_
#include "mwMachSimVerifier.hpp"
#include "mwvColor.hpp"
#include "mwvMeasurementPoint.hpp"

#include <mwString.hpp>


namespace VerifierUtil
{
struct Margins
{
	Margins() : Top(0), Right(0), Bottom(0), Left(0) {}
	Margins(int top, int right, int bottom, int left)
		: Top(top), Right(right), Bottom(bottom), Left(left)
	{
	}

	int Top, Right, Bottom, Left;
};

class MW_VERIFIER_API LabelAppearance
{
	typedef VerifierUtil::mwvColor mwvColor;

public:
	LabelAppearance()
		: m_cBack(mwvColor(1.0f, 1.0f, 1.0f, 0.2f)),
		  m_cText(mwvColor(0.0f, 0.0f, 0.0f, 0.2f)),
		  m_cBorder(mwvColor(0.0f, 0.0f, 0.0f, 0.2f)),
		  m_bUseShadow(true),
		  m_bUseTransparency(true),
		  m_Font("Lucida Unicode"),
		  m_FontSize(12),
		  m_PinLength(30),
		  m_fCornerSize(8),
		  m_fPinPointSize(6),
		  m_fShadowWidth(8),
		  m_fLineWidth(1)
	{
	}

	/// Getter Method for m_cBack Property
	mwvColor GetBack() const { return m_cBack; }
	/// Setter Method for m_cBack Property
	void SetBack(mwvColor val) { m_cBack = val; }
	/// Getter Method for m_cText Property
	mwvColor GetText() const { return m_cText; }
	/// Setter Method for m_cText Property
	void SetText(mwvColor val) { m_cText = val; }
	/// Getter Method for m_cText Property
	mwvColor GetBorder() const { return m_cBorder; }
	/// Setter Method for m_cText Property
	void SetBorder(mwvColor val) { m_cBorder = val; }
	/// Getter Method for m_bUseShadow Property
	bool GetUseShadow() const { return m_bUseShadow; }
	/// Setter Method for m_bUseShadow Property
	void SetUseShadow(bool val) { m_bUseShadow = val; }
	/// Getter Method for m_bUseTransparency Property
	bool GetUseTransparency() const { return m_bUseTransparency; }
	/// Setter Method for m_bUseTransparency Property
	void SetUseTransparency(bool val) { m_bUseTransparency = val; }
	/// Getter Method for m_Font Property
	misc::mwstring GetFont() const { return m_Font; }
	/// Setter Method for m_Font Property
	void SetFont(misc::mwstring val) { m_Font = val; }
	/// Getter Method for m_FontSize Property
	int GetFontSize() const { return m_FontSize; }
	/// Setter Method for m_FontSize Property
	void SetFontSize(int val) { m_FontSize = val; }
	/// Getter Method for m_PinLength Property
	float GetPinLength() const { return m_PinLength; }
	/// Setter Method for m_PinLength Property
	void SetPinLength(float val) { m_PinLength = val; }
	/// Getter Method for m_fPinPointSize Property
	float GetPinPointSize() const { return m_fPinPointSize; }
	/// Setter Method for m_fPinPointSize Property
	void SetPinPointSize(float val) { m_fPinPointSize = val; }
	/// Getter Method for m_fShadowWidth Property
	float GetShadowWidth() const { return m_fShadowWidth; }
	/// Setter Method for m_fShadowWidth Property
	void SetShadowWidth(float val) { m_fShadowWidth = val; }
	/// Getter Method for m_fCornerSize Property
	float GetCornerSize() const { return m_fCornerSize; }
	/// Setter Method for m_fCornerSize Property
	void SetCornerSize(float val) { m_fCornerSize = val; }

	float GetLineWidth() const { return m_fLineWidth; }
	void SetLineWidth(float v) { m_fLineWidth = v; }

	void SetMargins(const Margins& rect) { m_margins = rect; }
	Margins GetMargins() const { return m_margins; }

protected:
	mwvColor m_cBack;
	mwvColor m_cText;
	mwvColor m_cBorder;
	bool m_bUseShadow;
	bool m_bUseTransparency;
	misc::mwstring m_Font;
	int m_FontSize;
	float m_PinLength;
	float m_fPinPointSize;
	float m_fShadowWidth;
	float m_fCornerSize;
	float m_fLineWidth;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Margins m_margins;
};

class MW_VERIFIER_API mwvDrawLabelsHandler
{
public:
	mwvDrawLabelsHandler(void);
	~mwvDrawLabelsHandler(void){};

	/// Create a  Text for a Gouge Label
	///
	/// Uses the information in rep and creates with the related data in  the handler the label text
	/// @param rep the report data of mwMachSimVerifier::GougeReport
	/// @param deviationOffset actual offsett used
	/// @return  The created Gouge Label as a Text of misc::mwstring
	misc::mwstring CreateGougeLabelText(
		mwMachSimVerifier::GougeReport const& rep, float deviationOffset);

	/// Create a  Text for a excess Label
	///
	/// Uses the information in rep and creates with the related data in  the handler the label text
	/// @param rep the report data of mwMachSimVerifier::GougeReport
	/// @param deviationOffset actual offsett used
	/// @return  The created Gouge Label as a Text of misc::mwstring
	misc::mwstring CreateExcessLabelText(
		mwMachSimVerifier::GougeReport const& rep, float deviationOffset);

	/// Create a Label Text
	///
	/// Add the information in rep to the text in lable called by CreateGougeLabelText() and
	/// CreateExcessLabelText() @param [in] line  the text to which the information will be added of
	/// misc::mwstring @param [in] rep the information which will be put into the text of
	/// mwMachSimVerifier::GougeReport const @param [out] label result as of misc::mwstring @param
	/// [in] deviationOffset the offset used to the data of float
	void CreateLabelText(
		misc::mwstring& line,
		mwMachSimVerifier::GougeReport const& rep,
		misc::mwstring& label,
		float deviationOffset);

	/// Creates a text for a Point Label
	///
	/// Use the information in the parameters and creates with the related data in  the handler the
	/// label text
	/// @param [in] p the point which is inspected of mwvMeasurementPoint
	/// @param [in] drawMode current draw mode to be able to distinguish the additional data
	///		between part number and deviation
	/// @return  The created Point Label as a Text of misc::mwstring
	misc::mwstring CreatePointLabelText(
		mwvMeasurementPoint const& p,
		mwMachSimVerifier::WorkpieceDrawModes const& drawMode,
		float deviationOffset);

	/// Create a Distance Label Text
	///
	/// Create the text label for the distance measure
	/// @param [in] distance	to be written on the label
	/// @return The created Distance Label Text of misc::mwstring
	misc::mwstring CreateDistanceLabelText(float distance);

	/// Concat
	///
	/// Concatenates two strings label and line returning the result string
	/// @param [in] label of misc::mwstring
	/// @param [in] line of misc::mwstring
	/// @return Concat result of misc::mwstring
	misc::mwstring Concat(misc::mwstring label, misc::mwstring line);

	/// Add Line Delimiter
	///
	/// Add the line delimiter to the string in text returing the result string
	/// @param [in] text	of misc::mwstring
	/// @return result with the delimiter of misc::mwstring
	misc::mwstring AddLineDelimiter(misc::mwstring text);

	/// Verify number of arguments for Boost Format
	///
	/// A routine which validates the string if the expected number of argument positions are avail
	/// in the string. @param [in] texttotest the text string whose argument entries shall be
	/// checked
	/// @param [in] numberOfArgumentsExpected of int
	bool VerifyForBoostFormat(const misc::mwstring& texttotest, int numberOfArgumentsExpected);

	/// Apply Text Mask
	///
	/// Apply the texts in mask to descriptive strings for the labels.
	///	Checks if valid numbers of argument fields are valid.
	void ApplyTextMask(mwMachSimVerifier::LabelTextMask mask);


	/// Getter Method for m_sGougeDescription Property
	misc::mwstring GetGougeDescription() const { return m_sGougeDescription; }
	/// Setter Method for m_sGougeDescription Property
	void SetGougeDescription(misc::mwstring val) { m_sGougeDescription = val; }
	/// Getter Method for m_sExcessDescription Property
	misc::mwstring GetExcessDescription() const { return m_sExcessDescription; }
	/// Setter Method for m_sExcessDescription Property
	void SetExcessDescription(misc::mwstring val) { m_sExcessDescription = val; }
	/// Getter Method for m_sPointDescription Property
	misc::mwstring GetPointDescription() const { return m_sPointDescription; }
	/// Setter Method for m_sPointDescription Property
	void SetPointDescription(misc::mwstring val) { m_sPointDescription = val; }
	/// Getter Method for m_sPosition Property
	misc::mwstring GetPosition() const { return m_sPosition; }
	/// Setter Method for m_sPosition Property
	void SetPosition(misc::mwstring val) { m_sPosition = val; }
	/// Getter Method for m_sDeviation Property
	misc::mwstring GetDeviation() const { return m_sDeviation; }
	/// Setter Method for m_seDeviation Property
	void SetDeviation(misc::mwstring val) { m_sDeviation = val; }
	/// Getter Method for m_sAbsoluteDeviation Property
	misc::mwstring GetAbsoluteDeviation() const { return m_sAbsoluteDeviation; }
	/// Setter Method for m_sAbsoluteDeviation Property
	void SetAbsoluteDeviation(misc::mwstring val) { m_sAbsoluteDeviation = val; }
	/// Getter Method for m_sRelativeDeviation Property
	misc::mwstring GetRelativeDeviation() const { return m_sRelativeDeviation; }
	/// Setter Method for m_sRelativeDeviation Property
	void SetRelativeDeviation(misc::mwstring val) { m_sRelativeDeviation = val; }
	/// Getter Method for m_sChunkNumber Property
	misc::mwstring GetChunkNumber() const { return m_sChunkNumber; }
	/// Setter Method for m_sChunkNumber Property
	void SetChunkNumber(misc::mwstring val) { m_sChunkNumber = val; }
	/// Getter Method for m_sBlockNumber Property
	misc::mwstring GetBlockNumber() const { return m_sBlockNumber; }
	/// Setter Method for m_sBlockNumber Property
	void SetBlockNumber(misc::mwstring val) { m_sBlockNumber = val; }
	/// Getter Method for m_sToolNumber Property
	misc::mwstring GetToolNumber() const { return m_sToolNumber; }
	/// Setter Method for m_sToolNumber Property
	void SetToolNumber(misc::mwstring val) { m_sToolNumber = val; }
	/// Getter Method for m_sOperationNumber Property
	misc::mwstring GetOperationNumber() const { return m_sOperationNumber; }
	/// Setter Method for m_sOperationNumber Property
	void SetOperationNumber(misc::mwstring val) { m_sOperationNumber = val; }
	/// Getter Method for m_sCollisionWarning Property
	misc::mwstring GetCollisionWarning() const { return m_sCollisionWarning; }
	/// Setter Method for m_sCollisionWarning Property
	void SetCollisionWarning(misc::mwstring val) { m_sCollisionWarning = val; }
	/// Getter Method for m_sDistance Property
	misc::mwstring GetDistance() const { return m_sDistance; }
	/// Setter Method for m_sDistance Property
	void SetDistance(misc::mwstring val) { m_sDistance = val; }
	/// Getter Method for m_aGouges Property
	const VerifierUtil::LabelAppearance& GetGouges() const { return m_aGouges; }
	/// Setter Method for m_aGouges Property
	void SetGouges(const VerifierUtil::LabelAppearance& val) { m_aGouges = val; }
	/// Getter Method for m_aExcess Property
	const VerifierUtil::LabelAppearance& GetExcess() const { return m_aExcess; }
	/// Setter Method for m_aExcess Property
	void SetExcess(const VerifierUtil::LabelAppearance& val) { m_aExcess = val; }
	/// Getter Method for m_aPoints Property
	const VerifierUtil::LabelAppearance& GetPoints() const { return m_aPoints; }
	/// Setter Method for m_aPoints Property
	void SetPoints(const VerifierUtil::LabelAppearance& val) { m_aPoints = val; }
	/// Getter Method for m_aDistances Property
	const VerifierUtil::LabelAppearance& GetDistances() const { return m_aDistances; }
	/// Setter Method for m_aDistances Property
	void SetDistances(const VerifierUtil::LabelAppearance& val) { m_aDistances = val; }
	/// Getter Method for m_aRubberBandBox Property
	const VerifierUtil::LabelAppearance& GetRubberBandBox() const { return m_aRubberBandBox; }
	/// Setter Method for m_aRubberBandBox Property
	void SetRubberBandBox(const VerifierUtil::LabelAppearance& val) { m_aRubberBandBox = val; }


protected:
	misc::mwstring m_sGougeDescription;
	misc::mwstring m_sExcessDescription;
	misc::mwstring m_sPointDescription;

	misc::mwstring m_sPosition;
	misc::mwstring m_sDeviation;
	misc::mwstring m_sAbsoluteDeviation;
	misc::mwstring m_sRelativeDeviation;
	misc::mwstring m_sChunkNumber;
	misc::mwstring m_sBlockNumber;
	misc::mwstring m_sToolNumber;
	misc::mwstring m_sOperationNumber;
	misc::mwstring m_sCollisionWarning;
	misc::mwstring m_sDistance;
	misc::mwstring m_sTargetID;

	LabelAppearance m_aGouges;
	LabelAppearance m_aExcess;
	LabelAppearance m_aPoints;
	LabelAppearance m_aDistances;
	LabelAppearance m_aRubberBandBox;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVDRAWLABELSHANDLER_HPP_

/**
 * @file AResponse.hpp
 * @brief 抽象応答クラスの定義
 */

#pragma once
#include <string>
#include <map>
#include "define.hpp"
#include "HttpHeader.hpp"
#include "StatusLine.hpp"
#include "ARequest.hpp"

class ARequest;

/**
 * @class AResponse
 * @brief HTTP応答の抽象基底クラス
 *
 * このクラスは、HTTP応答の基本構造と機能を提供します。
 */
class AResponse
{
private:
	std::string		uri_;				///< リクエストURI
	HttpHeader		request_header_;	///< リクエストヘッダ
	StatusLine		line_;				///< ステータスライン
	HttpHeader		response_header_;	///< レスポンスヘッダ
	ft::bytes_vec	body_;				///< レスポンスボディ

	AResponse(); ///< デフォルトコンストラクタ（private）

protected:
	/**
	 * @brief ステータスラインを設定
	 * @param inLine 設定するステータスライン
	 */
	void setLine(StatusLine const &inLine);

	/**
	 * @brief レスポンスヘッダを設定
	 * @param inHeader 設定するヘッダ
	 */
	void setHeader(HttpHeader const &inHeader);

	/**
	 * @brief レスポンスボディをバイトベクトルで設定
	 * @param body 設定するボディ
	 */
	void setBody(ft::bytes_vec const &body);

	/**
	 * @brief レスポンスボディを文字列で設定
	 * @param body 設定するボディ
	 */
	void setBody(std::string const &body);

public:
	/**
	 * @brief コンストラクタ
	 * @param uri リクエストURI
	 * @param req_header リクエストヘッダ
	 */
	AResponse(std::string const &uri, HttpHeader const &req_header);

	/**
	 * @brief 仮想デストラクタ
	 */
	virtual ~AResponse();

	/**
	 * @brief コピーコンストラクタ
	 * @param rhs コピー元のオブジェクト
	 */
	AResponse(AResponse const &rhs);

	/**
	 * @brief 代入演算子
	 * @param rhs 代入元のオブジェクト
	 * @return 代入後の自身への参照
	 */
	AResponse &operator=(AResponse const &rhs);

	/**
	 * @brief ステータスラインを取得
	 * @return 現在のステータスライン
	 */
	StatusLine getLine(void) const;

	/**
	 * @brief レスポンスヘッダを取得
	 * @return 現在のレスポンスヘッダ
	 */
	HttpHeader getHeader(void) const;

	/**
	 * @brief レスポンスボディを取得
	 * @return 現在のレスポンスボディ
	 */
	ft::bytes_vec getBody(void) const;

	/**
	 * @brief レスポンスを生成する純粋仮想関数
	 * @return 生成されたレスポンス
	 */
	virtual ft::bytes_vec generateResponse(void) = 0;
};

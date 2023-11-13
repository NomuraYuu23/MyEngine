#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <dxcapi.h>

#pragma comment(lib, "dxcompiler.lib")

#include "../base/DirectXCommon.h"

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4x4.h"
#include "VertexData.h"
#include "TransformationMatrix.h"
#include "TransformStructure.h"

#include "Material.h"

#include "WorldTransform.h"
#include "ViewProjection.h"

#include <list>

class Model
{

public:

	struct MaterialData {
		std::string textureFilePath;
	};

	struct ModelData {

		std::vector<VertexData> vertices;
		MaterialData material;

	};

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device,
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature,
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState);

	/// <summary>
	/// 静的前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dモデル生成
	/// </summary>
	/// <returns></returns>
	static Model* Create(const std::string& directoryPath, const std::string& filename, DirectXCommon* dxCommon);

private:

	// デバイス
	static ID3D12Device* sDevice;
	// ディスクリプタサイズ
	static UINT sDescriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList* sCommandList;
	// ルートシグネチャ
	static Microsoft::WRL::ComPtr<ID3D12RootSignature> sRootSignature;
	// パイプラインステートオブジェクト
	static Microsoft::WRL::ComPtr<ID3D12PipelineState> sPipelineState;
	//計算
	static Matrix4x4Calc* matrix4x4Calc;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::string& directoryPath, const std::string& filename, DirectXCommon* dxCommon);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(WorldTransform& worldTransform, const ViewProjection& viewProjection);
	void Draw(WorldTransform& worldTransform, const ViewProjection& viewProjection, Material* material);

	/// <summary>
	/// メッシュデータ生成
	/// </summary>
	void CreateMesh(const std::string& directoryPath, const std::string& filename);

	Model::MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

	//objファイルを読む
	Model::ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);


	/// <summary>
	/// テクスチャハンドルの設定
	/// </summary>
	/// <param name="textureHandle"></param>
	void SetTextureHandle(uint32_t textureHandle);

	uint32_t GetTevtureHandle() { return textureHandle_; }

private:
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff_;
	// 頂点バッファマップ
	VertexData* vertMap = nullptr;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView_{};

	//モデル読み込み
	Model::ModelData modelData;

	//テクスチャ番号
	UINT textureHandle_ = 0;
	// リソース設定
	D3D12_RESOURCE_DESC resourceDesc_;

	// インスタンスカウント
	UINT instanceCount_;

	// デフォルトマテリアル
	std::unique_ptr<Material> defaultMaterial_;

};

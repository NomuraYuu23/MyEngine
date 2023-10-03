#pragma once
#include <wrl.h>
#include <d3d12.h>
class BufferResource
{

public:
	//Resource作成関数化
	static Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(Microsoft::WRL::ComPtr<ID3D12Device> device, const size_t& sizeInBytes);

};


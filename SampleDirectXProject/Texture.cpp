#include "Texture.h"
#include "GraphicsEngine.h"
#include <DirectXTex.h>
#include <iostream>

Texture::Texture(const wchar_t* full_path) : Resource(full_path)
{
	DirectX::ScratchImage image_data;
	
	std::wstring w = std::wstring(full_path);
	std::string s = std::string(w.begin(), w.end());

	std::cout << s << std::endl;

	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(GraphicsEngine::get()->getRenderSystem()->m_d3d_device, image_data.GetImages(),
			image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateShaderResourceView(m_texture, &desc,
			&m_shader_res_view);
 		std::cout << "success" << std::endl;
	}
	else
	{
		std::cout << "fail" << std::endl;
		throw std::exception("Texture not created successfully");
	}
}

Texture::~Texture()
{
	m_shader_res_view->Release();
	m_texture->Release();
}

/* Copyright (c) 2018-2024, Arm Limited and Contributors
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 the "License";
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "common/vk_common.h"
#include "core/instance.h"
#include "platform/application.h"

/**
 * @brief A self-contained (minimal use of framework) sample that illustrates
 * the rendering of a triangle
 */
class HelloTriangle : public vkb::Application
{
	/**
	 * @brief Swapchain state
	 */
	struct SwapchainDimensions
	{
		/// Width of the swapchain.
		uint32_t width = 0;

		/// Height of the swapchain.
		uint32_t height = 0;

		/// Pixel format of the swapchain.
		VkFormat format = VK_FORMAT_UNDEFINED;
	};

	/**
	 * @brief Per-frame data
	 */
	struct PerFrame
	{
		VkDevice device = VK_NULL_HANDLE;

		VkFence queue_submit_fence = VK_NULL_HANDLE;

		VkCommandPool primary_command_pool = VK_NULL_HANDLE;

		std::vector<VkCommandBuffer> primary_command_buffers;

		VkSemaphore swapchain_acquire_semaphore = VK_NULL_HANDLE;

		VkSemaphore swapchain_release_semaphore = VK_NULL_HANDLE;

		int32_t queue_index;
	};

	/**
	 * @brief Vulkan objects and global state
	 */
	struct Context
	{
		/// The Vulkan instance.
		VkInstance instance = VK_NULL_HANDLE;

		/// The Vulkan physical device.
		VkPhysicalDevice gpu = VK_NULL_HANDLE;

		/// The Vulkan device.
		VkDevice device = VK_NULL_HANDLE;

		/// The Vulkan device queue.
		VkQueue queue = VK_NULL_HANDLE;

		/// The swapchain.
		VkSwapchainKHR swapchain = VK_NULL_HANDLE;

		/// The swapchain dimensions.
		SwapchainDimensions swapchain_dimensions;

		/// The surface we will render to.
		VkSurfaceKHR surface = VK_NULL_HANDLE;

		/// The queue family index where graphics work will be submitted.
		int32_t graphics_queue_index = -1;

		/// The image view for each swapchain image.
		std::vector<VkImageView> swapchain_image_views;
        std::vector<VkImage> swapchain_images;

		/// The framebuffer for each swapchain image view.
		// std::vector<VkFramebuffer> swapchain_framebuffers;

		/// The renderpass description.
		// VkRenderPass render_pass = VK_NULL_HANDLE;

		/// The graphics pipeline.
		VkPipeline pipeline = VK_NULL_HANDLE;

		/**
		 * The pipeline layout for resources.
		 * Not used in this sample, but we still need to provide a dummy one.
		 */
		VkPipelineLayout pipeline_layout = VK_NULL_HANDLE;

		/// The debug utility callback.
		VkDebugUtilsMessengerEXT debug_callback = VK_NULL_HANDLE;

		/// A set of semaphores that can be reused.
		std::vector<VkSemaphore> recycled_semaphores;

		/// A set of per-frame data.
		std::vector<PerFrame> per_frame;
	};

  public:
	HelloTriangle();

	virtual ~HelloTriangle();

	virtual bool prepare(const vkb::ApplicationOptions &options) override;

	virtual void update(float delta_time) override;

	virtual bool resize(const uint32_t width, const uint32_t height) override;

	bool validate_extensions(const std::vector<const char *>          &required,
	                         const std::vector<VkExtensionProperties> &available);

	bool validate_layers(const std::vector<const char *>      &required,
	                     const std::vector<VkLayerProperties> &available);

	VkShaderStageFlagBits find_shader_stage(const std::string &ext);

	void init_instance();

	void init_device();

	void init_per_frame(PerFrame &per_frame);

	// void init_render_pass(Context &context);

	void init_swapchain();

	void init_render_pass();

	VkShaderModule load_shader_module(const char *path);

	void init_pipeline();

	VkResult acquire_next_image(uint32_t *image);

	// void init_framebuffers(Context &context);

	// void teardown_framebuffers(Context &context);

    void record_command_buffers(Context& contex);

    void HelloTriangle::record_triangle(Context& context, VkCommandBuffer& cmd);

    void HelloTriangle::record_square(Context& context, VkCommandBuffer& cmd);

	void init_framebuffers();

  private:
	Context context;

	std::unique_ptr<vkb::Instance> vk_instance;
    std::vector<std::function<void(HelloTriangle*, Context&, VkCommandBuffer&)>> record_functions;
};

std::unique_ptr<vkb::Application> create_hello_triangle();


enum class mesh_cmd : u16 {
	_2d_col = 16,
	_2d_tex,
	_2d_tex_col,
	_3d_tex,
	_3d_tex_instanced,
	lines,
	cubemap,
	chunk,
	skydome
};

#pragma pack(push, 1)
struct chunk_vertex {
	
	u8 v = 0, u = 0, z = 0, x = 0;
	u32 aoty = 0;
	u32 ln = 0;

	static chunk_vertex from_vec(v3 v, v3 uv, bv4 ao, u8 n_idx);
};
#pragma pack(pop)
static_assert(sizeof(chunk_vertex) == 12, "chunk_vertex size != 12");

struct mesh_chunk {

	vector<chunk_vertex> 	vertices;
	vector<uv3> 			elements;

	gpu_object_id gpu = -1;
	bool dirty = false;

	static mesh_chunk make_cpu(u32 verts = 8192, allocator* alloc = null);
	void init_gpu();
	void destroy();
	void free_cpu();
	void clear();
	void swap_mesh(mesh_chunk other);

	void unit_quad(v3 p1, v3 p2, v3 p3, v3 p4, v3 uv_ext, bv4 ao, u8 n_idx);
	void cube_no_norm(v3 pos, f32 len);
};

struct mesh_cubemap {
	v3 vertices[36] = {
		{-1.0f,  1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f, -1.0f,  1.0f},
		{-1.0f, -1.0f, -1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f,  1.0f,  1.0f},
		{-1.0f, -1.0f,  1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f,  1.0f},
		{-1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{-1.0f, -1.0f,  1.0f},
		{-1.0f,  1.0f, -1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{-1.0f,  1.0f,  1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f,  1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f,  1.0f},
		{ 1.0f, -1.0f,  1.0f}
	};

	gpu_object_id gpu = -1;
	bool dirty = false;

	void init();
	void destroy();
};

struct mesh_lines {
	vector<v3> 	   vertices;
	vector<colorf> colors;
	
	gpu_object_id gpu = -1;
	bool dirty = false;

	void init(allocator* alloc = null);
	void destroy();

	void push(v3 p1, v3 p2, colorf c1 = colorf(0,0,0,1), colorf c2 = colorf(0,0,0,1));
};

struct mesh_2d_col {
	vector<v2>		vertices;	// x y 
	vector<colorf>	colors;		// r g b a
	vector<uv3> 	elements;

	gpu_object_id gpu = -1;
	bool dirty = false;

	void init(allocator* alloc = null);
	void destroy();
	void clear();
	bool empty();

	void push_tri(v2 p1, v2 p2, v2 p3, color c);
	void push_rect(r2 rect, color c);
	void push_cutrect(r2 r, f32 round, color c);
};

struct mesh_2d_tex {
	vector<v2>		vertices;	// x y 
	vector<v2>		texCoords;	// u v
	vector<uv3> 	elements;

	gpu_object_id gpu = -1;
	bool dirty = false;

	void init(allocator* alloc = null);
	void destroy();
	void clear();
	bool empty();
};

struct mesh_2d_tex_col {
	vector<v2>		vertices;	// x y 
	vector<v2>		texCoords;	// u v
	vector<colorf> 	colors;
	vector<uv3> 	elements;

	gpu_object_id gpu = -1;
	bool dirty = false;

	void init(allocator* alloc = null);
	void destroy();
	void clear();
	bool empty();

	void push_rect(r2 rect, color c);
	void push_cutrect(r2 r, f32 round, color c);
	f32 push_text_line(asset* font, string text_utf8, v2 pos, f32 point = 0.0f, color c = color(255, 255, 255, 255)); 
};

struct mesh_3d_tex {
	vector<v3>  vertices;	// x y z
	vector<v2>  texCoords; 	// u v
	vector<uv3> elements;

	gpu_object_id gpu = -1;
	bool dirty = false;

	void init(allocator* alloc = null);
	void destroy();
	void clear();
	bool empty();

	void push_cube(v3 pos, f32 len);
	void push_dome(v3 center, f32 r, i32 divisions);
};

struct mesh_3d_tex_instance_data {
	
	mesh_3d_tex* parent = null;
	vector<v3> data;

	u32 instances = 0;

	gpu_object_id gpu = -1;
	bool dirty = false;

	void init(mesh_3d_tex* parent, u32 instances = 32, allocator* alloc = null);
	void destroy();
	void clear();
	bool empty();
};

void setup_mesh_commands();

#define decl_mesh(name) \
	CALLBACK void uniforms_mesh_##name(shader_program* prog, render_command* cmd); 	\
	CALLBACK void setup_mesh_##name(gpu_object* obj); 								\
	CALLBACK void update_mesh_##name(gpu_object* obj, void* data, bool force);		\
	CALLBACK void run_mesh_##name(render_command* cmd, gpu_object* gpu);			\
	CALLBACK bool compat_mesh_##name(ogl_info* info);

#define register_mesh(name) \
	eng->ogl.add_command((u16)mesh_cmd::name, FPTR(run_mesh_##name), FPTR(uniforms_mesh_##name), FPTR(compat_mesh_##name), "shaders/" #name ".v"_, "shaders/" #name ".f"_);

#define register_mesh_g(name) \
	eng->ogl.add_command((u16)mesh_cmd::name, FPTR(run_mesh_##name), FPTR(uniforms_mesh_##name), FPTR(compat_mesh_##name), "shaders/" #name ".v"_, "shaders/" #name ".f"_, "shaders/" #name ".g"_);

#define register_mesh_ex(cmd, name, path) \
	eng->ogl.add_command((u16)mesh_cmd::cmd, FPTR(run_mesh_##name), FPTR(uniforms_mesh_##name), FPTR(compat_mesh_##name), "shaders/" path #name ".v"_, "shaders/" path #name ".f"_);

#define register_mesh_ex_g(cmd, name, path) \
	eng->ogl.add_command((u16)mesh_cmd::cmd, FPTR(run_mesh_##name), FPTR(uniforms_mesh_##name), FPTR(compat_mesh_##name), "shaders/" path #name ".v"_, "shaders/" path #name ".f"_, "shaders/" path #name ".g"_);

decl_mesh(skydome);
decl_mesh(cubemap);
decl_mesh(chunk);
decl_mesh(2d_col);
decl_mesh(2d_tex);
decl_mesh(2d_tex_col);
decl_mesh(3d_tex);
decl_mesh(3d_tex_instanced);
decl_mesh(lines);
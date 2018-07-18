
void setup_mesh_commands() { PROF
	
	register_mesh(lines);
	register_mesh(cubemap);
	register_mesh(skydome);
	register_mesh(chunk);

	register_mesh_ex(_2d_col, 2d_col, "mesh/");
	register_mesh_ex(_2d_tex, 2d_tex, "mesh/");
	register_mesh_ex(_2d_tex_col, 2d_tex_col, "mesh/");
	register_mesh_ex(_3d_tex_instanced, 3d_tex_instanced, "mesh/");
	
	register_mesh_ex_g(_3d_tex, 3d_tex, "mesh/");
}

CALLBACK void uniforms_mesh_skydome(shader_program* prog, render_command* cmd) { PROF

	world_time* time = (world_time*)cmd->uniform_info;

	GLint tloc = glGetUniformLocation(prog->handle, "transform");
	GLint dloc = glGetUniformLocation(prog->handle, "day_01");
	GLint sloc = glGetUniformLocation(prog->handle, "sky");
	GLint nsloc = glGetUniformLocation(prog->handle, "night_sky");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniform1i(sloc, 0);
	glUniform1i(nsloc, 1);
	glUniform1f(dloc, time->day_01());
	glUniformMatrix4fv(tloc, 1, gl_bool::_false, transform.a);
}

CALLBACK void uniforms_mesh_cubemap(shader_program* prog, render_command* cmd) { PROF

	GLint loc = glGetUniformLocation(prog->handle, "transform");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniformMatrix4fv(loc, 1, gl_bool::_false, transform.a);
}

CALLBACK void uniforms_mesh_chunk(shader_program* prog, render_command* cmd) { PROF

	GLint loc = glGetUniformLocation(prog->handle, "transform");
	GLint szloc = glGetUniformLocation(prog->handle, "units_per_voxel");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniformMatrix4fv(loc, 1, gl_bool::_false, transform.a);
	glUniform1f(szloc, (f32)chunk::units_per_voxel);
}

CALLBACK void uniforms_mesh_2d_col(shader_program* prog, render_command* cmd) { PROF

	GLint loc = glGetUniformLocation(prog->handle, "transform");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniformMatrix4fv(loc, 1, gl_bool::_false, transform.a);
}

CALLBACK void uniforms_mesh_2d_tex(shader_program* prog, render_command* cmd) { PROF

	GLint loc = glGetUniformLocation(prog->handle, "transform");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniformMatrix4fv(loc, 1, gl_bool::_false, transform.a);
}

CALLBACK void uniforms_mesh_2d_tex_col(shader_program* prog, render_command* cmd) { PROF

	GLint loc = glGetUniformLocation(prog->handle, "transform");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniformMatrix4fv(loc, 1, gl_bool::_false, transform.a);
}

CALLBACK void uniforms_mesh_3d_tex(shader_program* prog, render_command* cmd) { PROF
	
	GLint loc = glGetUniformLocation(prog->handle, "transform");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniformMatrix4fv(loc, 1, gl_bool::_false, transform.a);
}

CALLBACK void uniforms_mesh_lines(shader_program* prog, render_command* cmd) { PROF
	
	GLint loc = glGetUniformLocation(prog->handle, "transform");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniformMatrix4fv(loc, 1, gl_bool::_false, transform.a);
}

CALLBACK void uniforms_mesh_3d_tex_instanced(shader_program* prog, render_command* cmd) { PROF
	
	GLint loc = glGetUniformLocation(prog->handle, "transform");

	m4 transform = cmd->proj * cmd->view * cmd->model;

	glUniformMatrix4fv(loc, 1, gl_bool::_false, transform.a);
}

CALLBACK void update_mesh_skydome(gpu_object* obj, void* data, bool force) { PROF

	update_mesh_3d_tex(obj, data, force);
}

CALLBACK void update_mesh_cubemap(gpu_object* obj, void* data, bool force) { PROF

	mesh_cubemap* m = (mesh_cubemap*)data;
	if(!force && !m->dirty) return;

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glBufferData(gl_buf_target::array, 36 * sizeof(v3), m->vertices, gl_buf_usage::dynamic_draw);

	m->dirty = false;
}

CALLBACK void update_mesh_chunk(gpu_object* obj, void* data, bool force) { PROF

	mesh_chunk* m = (mesh_chunk*)data;
	if(!force && !m->dirty) return;

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glBufferData(gl_buf_target::array, m->vertices.size * sizeof(chunk_vertex), m->vertices.size ? m->vertices.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::element_array, obj->vbos[1]);
	glBufferData(gl_buf_target::element_array, m->elements.size * sizeof(uv3), m->elements.size ? m->elements.memory : null, gl_buf_usage::dynamic_draw);

	m->dirty = false;
}

CALLBACK void update_mesh_2d_col(gpu_object* obj, void* data, bool force) { PROF

	mesh_2d_col* m = (mesh_2d_col*)data;
	if(!force && !m->dirty) return;

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glBufferData(gl_buf_target::array, m->vertices.size * sizeof(v2), m->vertices.size ? m->vertices.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glBufferData(gl_buf_target::array, m->colors.size * sizeof(colorf), m->colors.size ? m->colors.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::element_array, obj->vbos[2]);
	glBufferData(gl_buf_target::element_array, m->elements.size * sizeof(uv3), m->elements.size ? m->elements.memory : null, gl_buf_usage::dynamic_draw);

	m->dirty = false;
}

CALLBACK void update_mesh_2d_tex(gpu_object* obj, void* data, bool force) { PROF

	mesh_2d_tex* m = (mesh_2d_tex*)data;
	if(!force && !m->dirty) return;

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glBufferData(gl_buf_target::array, m->vertices.size * sizeof(v2), m->vertices.size ? m->vertices.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glBufferData(gl_buf_target::array, m->texCoords.size * sizeof(v2), m->texCoords.size ? m->texCoords.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::element_array, obj->vbos[2]);
	glBufferData(gl_buf_target::element_array, m->elements.size * sizeof(uv3), m->elements.size ? m->elements.memory : null, gl_buf_usage::dynamic_draw);

	m->dirty = false;
}

CALLBACK void update_mesh_2d_tex_col(gpu_object* obj, void* data, bool force) { PROF

	mesh_2d_tex_col* m = (mesh_2d_tex_col*)data;
	if(!force && !m->dirty) return;

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glBufferData(gl_buf_target::array, m->vertices.size * sizeof(v2), m->vertices.size ? m->vertices.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glBufferData(gl_buf_target::array, m->texCoords.size * sizeof(v2), m->texCoords.size ? m->texCoords.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::array, obj->vbos[2]);
	glBufferData(gl_buf_target::array, m->colors.size * sizeof(colorf), m->colors.size ? m->colors.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::element_array, obj->vbos[3]);
	glBufferData(gl_buf_target::element_array, m->elements.size * sizeof(uv3), m->elements.size ? m->elements.memory : null, gl_buf_usage::dynamic_draw);

	m->dirty = false;
}

CALLBACK void update_mesh_3d_tex(gpu_object* obj, void* data, bool force) { PROF

	mesh_3d_tex* m = (mesh_3d_tex*)data;
	if(!force && !m->dirty) return;

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glBufferData(gl_buf_target::array, m->vertices.size * sizeof(v3), m->vertices.size ? m->vertices.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glBufferData(gl_buf_target::array, m->texCoords.size * sizeof(v2), m->texCoords.size ? m->texCoords.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::element_array, obj->vbos[2]);
	glBufferData(gl_buf_target::element_array, m->elements.size * sizeof(uv3), m->elements.size ? m->elements.memory : null, gl_buf_usage::dynamic_draw);

	m->dirty = false;
}

CALLBACK void update_mesh_lines(gpu_object* obj, void* data, bool force) { PROF

	mesh_lines* m = (mesh_lines*)data;
	if(!force && !m->dirty) return;

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glBufferData(gl_buf_target::array, m->vertices.size * sizeof(v3), m->vertices.size ? m->vertices.memory : null, gl_buf_usage::dynamic_draw);

	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glBufferData(gl_buf_target::array, m->colors.size * sizeof(colorf), m->colors.size ? m->colors.memory : null, gl_buf_usage::dynamic_draw);

	m->dirty = false;
}

CALLBACK void update_mesh_3d_tex_instanced(gpu_object* obj, void* d, bool force) { PROF

	mesh_3d_tex_instance_data* data = (mesh_3d_tex_instance_data*)d;
	mesh_3d_tex* m = data->parent;
	
	gpu_object* par_obj = eng->ogl.get_object(m->gpu);

	par_obj->update(par_obj, m, force);

	if(force || data->dirty) {

		glBindBuffer(gl_buf_target::array, obj->vbos[0]);
		glBufferData(gl_buf_target::array, data->data.size * sizeof(v3), data->data.size ? data->data.memory : null, gl_buf_usage::dynamic_draw);
	}

	data->dirty = false;
}

CALLBACK void run_mesh_skydome(render_command* cmd, gpu_object* gpu) { PROF

	run_mesh_3d_tex(cmd, gpu);
}

CALLBACK void run_mesh_cubemap(render_command* cmd, gpu_object* gpu) { PROF

	glDrawArrays(gl_draw_mode::triangles, 0, 36);
}

CALLBACK void run_mesh_chunk(render_command* cmd, gpu_object* gpu) { PROF

	mesh_chunk* m = (mesh_chunk*)gpu->data;

	u32 num_tris = ((cmd->num_tris ? cmd->num_tris : m->elements.size) - cmd->start_tri) * 3;
	glDrawElementsBaseVertex(gl_draw_mode::triangles, num_tris, gl_index_type::unsigned_int, (void*)(u64)(0), cmd->offset);
}

CALLBACK void run_mesh_2d_col(render_command* cmd, gpu_object* gpu) { PROF

	mesh_2d_col* m = (mesh_2d_col*)gpu->data;

	u32 num_tris = ((cmd->num_tris ? cmd->num_tris : m->elements.size) - cmd->start_tri) * 3;
	glDrawElementsBaseVertex(gl_draw_mode::triangles, num_tris, gl_index_type::unsigned_int, (void*)(u64)(0), cmd->offset);
}

CALLBACK void run_mesh_2d_tex(render_command* cmd, gpu_object* gpu) { PROF

	mesh_2d_tex* m = (mesh_2d_tex*)gpu->data;

	u32 num_tris = ((cmd->num_tris ? cmd->num_tris : m->elements.size) - cmd->start_tri) * 3;
	glDrawElementsBaseVertex(gl_draw_mode::triangles, num_tris, gl_index_type::unsigned_int, (void*)(u64)(0), cmd->offset);
}

CALLBACK void run_mesh_2d_tex_col(render_command* cmd, gpu_object* gpu) { PROF

	mesh_2d_tex_col* m = (mesh_2d_tex_col*)gpu->data;

	u32 num_tris = ((cmd->num_tris ? cmd->num_tris : m->elements.size) - cmd->start_tri) * 3;
	glDrawElementsBaseVertex(gl_draw_mode::triangles, num_tris, gl_index_type::unsigned_int, (void*)(u64)(0), cmd->offset);
}

CALLBACK void run_mesh_3d_tex(render_command* cmd, gpu_object* gpu) { PROF

	mesh_3d_tex* m = (mesh_3d_tex*)gpu->data;

	u32 num_tris = ((cmd->num_tris ? cmd->num_tris : m->elements.size) - cmd->start_tri) * 3;
	glDrawElementsBaseVertex(gl_draw_mode::triangles, num_tris, gl_index_type::unsigned_int, (void*)(u64)(0), cmd->offset);
}

CALLBACK void run_mesh_lines(render_command* cmd, gpu_object* gpu) { PROF

	mesh_lines* m = (mesh_lines*)gpu->data;

	glDrawArrays(gl_draw_mode::lines, 0, m->vertices.size);
}

CALLBACK void run_mesh_3d_tex_instanced(render_command* cmd, gpu_object* gpu) { PROF

	mesh_3d_tex_instance_data* data = (mesh_3d_tex_instance_data*)gpu->data;
	mesh_3d_tex* m = data->parent;

	u32 num_tris = ((cmd->num_tris ? cmd->num_tris : m->elements.size) - cmd->start_tri) * 3;

	glDrawElementsInstancedBaseVertex(gl_draw_mode::triangles, num_tris, gl_index_type::unsigned_int, (void*)(u64)(0), data->instances, cmd->offset);
}

CALLBACK bool compat_mesh_skydome(ogl_info* info) { PROF
	return info->check_version(3, 2);
}

CALLBACK bool compat_mesh_cubemap(ogl_info* info) { PROF
	return info->check_version(3, 2);
}

CALLBACK bool compat_mesh_chunk(ogl_info* info) { PROF
	return info->check_version(3, 2);
}

CALLBACK bool compat_mesh_2d_col(ogl_info* info) { PROF
	return info->check_version(3, 2);
}

CALLBACK bool compat_mesh_2d_tex(ogl_info* info) { PROF
	return info->check_version(3, 2);
}

CALLBACK bool compat_mesh_2d_tex_col(ogl_info* info) { PROF
	return info->check_version(3, 2);
}

CALLBACK bool compat_mesh_3d_tex(ogl_info* info) { PROF
	return info->check_version(3, 2);
}

CALLBACK bool compat_mesh_lines(ogl_info* info) { PROF
	return info->check_version(3, 2);
}

CALLBACK bool compat_mesh_3d_tex_instanced(ogl_info* info) { PROF
	return info->check_version(3, 3);
}

CALLBACK void setup_mesh_skydome(gpu_object* obj) { PROF

	setup_mesh_3d_tex(obj);
}

CALLBACK void setup_mesh_cubemap(gpu_object* obj) { PROF

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);

	glVertexAttribPointer(0, 3, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v3), (void*)0);
	glEnableVertexAttribArray(0);
}

CALLBACK void setup_mesh_chunk(gpu_object* obj) { PROF

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);

	glVertexAttribIPointer(0, 3, gl_vert_attrib_type::unsigned_int, sizeof(chunk_vertex), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(gl_buf_target::element_array, obj->vbos[1]);
}

CALLBACK void setup_mesh_2d_col(gpu_object* obj) { PROF

	glBindVertexArray(obj->vao);

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glVertexAttribPointer(0, 2, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v2), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glVertexAttribPointer(1, 4, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v4), (void*)0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(gl_buf_target::element_array, obj->vbos[2]);

	glBindVertexArray(0);
}

CALLBACK void setup_mesh_2d_tex(gpu_object* obj) { PROF

	glBindVertexArray(obj->vao);

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glVertexAttribPointer(0, 2, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v2), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glVertexAttribPointer(1, 2, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v2), (void*)0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(gl_buf_target::element_array, obj->vbos[2]);

	glBindVertexArray(0);
}

CALLBACK void setup_mesh_2d_tex_col(gpu_object* obj) { PROF

	glBindVertexArray(obj->vao);

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glVertexAttribPointer(0, 2, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v2), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glVertexAttribPointer(1, 2, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v2), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(gl_buf_target::array, obj->vbos[2]);
	glVertexAttribPointer(2, 4, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v4), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(gl_buf_target::element_array, obj->vbos[3]);

	glBindVertexArray(0);
}

CALLBACK void setup_mesh_3d_tex(gpu_object* obj) { PROF

	glBindVertexArray(obj->vao);

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glVertexAttribPointer(0, 3, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v3), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glVertexAttribPointer(1, 2, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v2), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(gl_buf_target::element_array, obj->vbos[2]);

	glBindVertexArray(0);
}

CALLBACK void setup_mesh_3d_tex_instanced(gpu_object* obj) { PROF

	glBindVertexArray(obj->vao);

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glVertexAttribPointer(2, 3, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v3), (void*)0);
	glVertexAttribDivisor(2, 1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

CALLBACK void setup_mesh_lines(gpu_object* obj) { PROF

	glBindVertexArray(obj->vao);

	glBindBuffer(gl_buf_target::array, obj->vbos[0]);
	glVertexAttribPointer(0, 3, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(v3), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(gl_buf_target::array, obj->vbos[1]);
	glVertexAttribPointer(1, 4, gl_vert_attrib_type::_float, gl_bool::_false, sizeof(colorf), (void*)0);
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}

void mesh_cubemap::init() {

	dirty = true;
	gpu = eng->ogl.add_object(FPTR(setup_mesh_cubemap), FPTR(update_mesh_cubemap), this);
}

void mesh_cubemap::destroy() {

	eng->ogl.destroy_object(gpu);
}

void mesh_lines::init(allocator* alloc) { PROF

	if(!alloc) alloc = CURRENT_ALLOC();

	vertices = vector<v3>::make(32, alloc);
	colors = vector<colorf>::make(32, alloc);
	gpu = eng->ogl.add_object(FPTR(setup_mesh_lines), FPTR(update_mesh_lines), this);
}

void mesh_lines::push(v3 p1, v3 p2, colorf c1, colorf c2) { PROF

	vertices.push(p1);
	vertices.push(p2);
	colors.push(c1);
	colors.push(c2);

	dirty = true;
}

void mesh_lines::destroy() { PROF

	vertices.destroy();
	colors.destroy();

	eng->ogl.destroy_object(gpu);
	gpu = -1;
}

void mesh_3d_tex_instance_data::init(mesh_3d_tex* par, u32 i, allocator* alloc) { PROF

	if(alloc == null) {
		alloc = CURRENT_ALLOC();
	}

	parent = par;
	data = vector<v3>::make(i, alloc);
	gpu = eng->ogl.add_object(FPTR(setup_mesh_3d_tex_instanced), FPTR(update_mesh_3d_tex_instanced), this);
}

void mesh_3d_tex_instance_data::destroy() { PROF

	data.destroy();

	eng->ogl.destroy_object(gpu);
	gpu = -1;
}

void mesh_3d_tex_instance_data::clear() { PROF

	data.clear();
	instances = 0;
	dirty = true;
}

bool mesh_3d_tex_instance_data::empty() { PROF

	return !data.size;
}

void mesh_2d_col::init(allocator* alloc) { PROF

	if(alloc == null) {
		alloc = CURRENT_ALLOC();
	}

	vertices = vector<v2>::make(1024, alloc);
	colors 	  =	vector<colorf>::make(1024, alloc);
	elements  = vector<uv3>::make(1024, alloc); 
	gpu = eng->ogl.add_object(FPTR(setup_mesh_2d_col), FPTR(update_mesh_2d_col), this);
}

void mesh_2d_col::destroy() { PROF

	vertices.destroy();
	colors.destroy();
	elements.destroy();

	eng->ogl.destroy_object(gpu);
	gpu = -1;
}

void mesh_2d_col::clear() { PROF
	vertices.clear();
	colors.clear();
	elements.clear();
	dirty = true;
}

bool mesh_2d_col::empty() { PROF

	return !vertices.size;
}

void mesh_2d_col::push_tri(v2 p1, v2 p2, v2 p3, color c) { PROF

	u32 idx = vertices.size;
	
	vertices.push(p1);
	vertices.push(p2);
	vertices.push(p3);

	DO(3) colors.push(c.to_f());

	elements.push(uv3(idx, idx + 1, idx + 2));

	dirty = true;
}

void mesh_2d_col::push_cutrect(r2 r, f32 round, color c) { PROF

	u32 idx = vertices.size;

	vertices.push(v2(r.x, r.y + round));
	vertices.push(v2(r.x, r.y + r.h - round));
	vertices.push(v2(r.x + round, r.y + r.h));
	vertices.push(v2(r.x + r.w - round, r.y + r.h));
	vertices.push(v2(r.x + r.w, r.y + r.h - round));
	vertices.push(v2(r.x + r.w, r.y + round));
	vertices.push(v2(r.x + r.w - round, r.y));
	vertices.push(v2(r.x + round, r.y));

	colorf cf = c.to_f();
	DO(8) colors.push(cf);

	elements.push(uv3(idx, idx + 1, idx + 2));
	elements.push(uv3(idx, idx + 2, idx + 7));
	elements.push(uv3(idx + 7, idx + 2, idx + 3));
	elements.push(uv3(idx + 7, idx + 6, idx + 3));
	elements.push(uv3(idx + 3, idx + 4, idx + 5));
	elements.push(uv3(idx + 3, idx + 5, idx + 6));

	dirty = true;
}

void mesh_2d_col::push_rect(r2 r, color c) { PROF

	u32 idx = vertices.size;

	vertices.push(v2(r.x, r.y + r.h));	// BLC
	vertices.push(r.xy);				// TLC
	vertices.push(r.xy + r.wh);		 	// BRC
	vertices.push(v2(r.x + r.w, r.y));	// TRC

	DO(4) colors.push(c.to_f());

	elements.push(uv3(idx, idx + 1, idx + 2));
	elements.push(uv3(idx + 1, idx + 2, idx + 3));

	dirty = true;
}


void mesh_2d_tex::init(allocator* alloc) { PROF

	if(alloc == null) {
		alloc = CURRENT_ALLOC();
	}

	vertices = vector<v2>::make(1024, alloc);
	texCoords =	vector<v2>::make(1024, alloc);
	elements  = vector<uv3>::make(1024, alloc); 
	gpu = eng->ogl.add_object(FPTR(setup_mesh_2d_tex), FPTR(update_mesh_2d_tex), this);
}

void mesh_2d_tex::destroy() { PROF

	vertices.destroy();
	texCoords.destroy();
	elements.destroy();

	eng->ogl.destroy_object(gpu);
	gpu = -1;
}

void mesh_2d_tex::clear() { PROF
	vertices.clear();
	texCoords.clear();
	elements.clear();

	dirty = true;
}

bool mesh_2d_tex::empty() { PROF

	return !vertices.size;
}

void mesh_2d_tex_col::init(allocator* alloc) { PROF

	if(alloc == null) {
		alloc = CURRENT_ALLOC();
	}

	vertices  = vector<v2>::make(1024, alloc);
	texCoords =	vector<v2>::make(1024, alloc);
	colors 	  = vector<colorf>::make(1024, alloc);
	elements  = vector<uv3>::make(1024, alloc); 
	gpu = eng->ogl.add_object(FPTR(setup_mesh_2d_tex_col), FPTR(update_mesh_2d_tex_col), this);
}

void mesh_2d_tex_col::destroy() { PROF

	vertices.destroy();
	texCoords.destroy();
	colors.destroy();
	elements.destroy();

	eng->ogl.destroy_object(gpu);
	gpu = -1;
}

void mesh_2d_tex_col::clear() { PROF
	vertices.clear();
	texCoords.clear();
	elements.clear();
	colors.clear();
}

bool mesh_2d_tex_col::empty() { PROF

	return !vertices.size;
}

void mesh_3d_tex::init(allocator* alloc) { PROF

	if(alloc == null) {
		alloc = CURRENT_ALLOC();
	}

	vertices = vector<v3>::make(1024, alloc);
	texCoords = vector<v2>::make(1024, alloc);
	elements  = vector<uv3>::make(1024, alloc);
	gpu = eng->ogl.add_object(FPTR(setup_mesh_3d_tex), FPTR(update_mesh_3d_tex), this);
}

void mesh_3d_tex::destroy() { PROF

	vertices.destroy();
	texCoords.destroy();
	elements.destroy();

	eng->ogl.destroy_object(gpu);
	gpu = -1;
}

void mesh_3d_tex::clear() { PROF
	vertices.clear();
	texCoords.clear();
	elements.clear();
}

bool mesh_3d_tex::empty() { PROF

	return !vertices.size;
}

f32 mesh_2d_tex_col::push_text_line(asset* font, string text_utf8, v2 pos, f32 point, color c) { PROF

	colorf cf = c.to_f();
	f32 x = pos.x;
	f32 y = pos.y;
	f32 scale = point / font->raster_font.point;
	if(point == 0.0f) {
		scale = 1.0f;
	}
	y += scale * font->raster_font.linedist;

	u32 index = 0;
	while(u32 codepoint = text_utf8.get_next_codepoint(&index)) {

		u32 idx = vertices.size;
		glyph_data glyph = font->raster_font.get_glyph(codepoint);

		f32 w = (f32)font->raster_font.width;
		f32 h = (f32)font->raster_font.height;
		v2 tlc (glyph.x1/w, 1.0f - glyph.y1/h);
		v2 brc (glyph.x2/w, 1.0f - glyph.y2/h);
		v2 trc (glyph.x2/w, 1.0f - glyph.y1/h);
		v2 blc (glyph.x1/w, 1.0f - glyph.y2/h);

		vertices.push(v2(x + scale*glyph.xoff1, y + scale*glyph.yoff2)); 	// BLC
 		vertices.push(v2(x + scale*glyph.xoff1, y + scale*glyph.yoff1));	// TLC
 		vertices.push(v2(x + scale*glyph.xoff2, y + scale*glyph.yoff2));	// BRC
 		vertices.push(v2(x + scale*glyph.xoff2, y + scale*glyph.yoff1));	// TRC

		texCoords.push(blc);
		texCoords.push(tlc);
		texCoords.push(brc);
		texCoords.push(trc);

		DO(4) colors.push(cf);

		elements.push(uv3(idx, idx + 1, idx + 2));
		elements.push(uv3(idx + 1, idx + 2, idx + 3));

		x += scale * glyph.advance;
	}

	dirty = true;
	return scale * font->raster_font.linedist;
}

// Concept from https://github.com/fogleman/Craft
void mesh_3d_tex::push_dome(v3 center, f32 r, i32 divisions) { PROF

	i32 p_divisions = divisions / 2 + 1;

	f32 th = 0.0f;
	for(i32 i = 0; i <= divisions; i++) {

		f32 ph = 0.0f;
		for(i32 j = 0; j < p_divisions; j++) {

			f32 ct = cos(th), st = sin(th), sp = sin(ph), cp = cos(ph);
			v3 point = v3(r * ct * sp, r * cp, r * st * sp);

			vertices.push(center + point);
			texCoords.push(v2(th / (2.0f * PI32), (0.5f * cp) + 0.5f));
			// texCoords.push(v2(th / (2.0f * PI32), ph / (1.0f * PI32)));

			ph += (PI32 * 2.0f) / divisions;
		}

		th += (PI32 * 2.0f) / divisions;
	}

	for (int x = 0; x < divisions; x++) {
		for (int y = 0; y < p_divisions - 1; y++) {
			GLuint idx = x * p_divisions + y;

			i32 idx1 = (idx + 1);
			i32 idxp = (idx + p_divisions);
			i32 idxp1 = (idx + p_divisions + 1);

			elements.push(uv3(idx, idx1, idxp));
			elements.push(uv3(idx1, idxp, idxp1));
		}
	}

	dirty = true;
}

void mesh_3d_tex::push_cube(v3 pos, f32 len) {

	u32 idx = vertices.size;

	f32 len2 = len / 2.0f;
	vertices.push(pos + v3( len2,  len2,  len2));
	vertices.push(pos + v3(-len2,  len2,  len2));
	vertices.push(pos + v3( len2, -len2,  len2));
	vertices.push(pos + v3( len2,  len2, -len2));
	vertices.push(pos + v3(-len2, -len2,  len2));
	vertices.push(pos + v3( len2, -len2, -len2));
	vertices.push(pos + v3(-len2,  len2, -len2));
	vertices.push(pos + v3(-len2, -len2, -len2));

	texCoords.push(v2(0.0f, 0.0f));
	texCoords.push(v2(1.0f, 0.0f));
	texCoords.push(v2(0.0f, 1.0f));
	texCoords.push(v2(0.0f, 0.0f));
	texCoords.push(v2(1.0f, 0.0f));
	texCoords.push(v2(0.0f, 1.0f));
	texCoords.push(v2(1.0f, 0.0f));
	texCoords.push(v2(1.0f, 1.0f));	

	elements.push(uv3(idx + 0, idx + 3, idx + 6));
	elements.push(uv3(idx + 0, idx + 3, idx + 5));
	elements.push(uv3(idx + 0, idx + 1, idx + 6));
	elements.push(uv3(idx + 1, idx + 4, idx + 7));
	elements.push(uv3(idx + 1, idx + 6, idx + 7));
	elements.push(uv3(idx + 4, idx + 2, idx + 5));
	elements.push(uv3(idx + 4, idx + 7, idx + 5));
	elements.push(uv3(idx + 7, idx + 5, idx + 3));
	elements.push(uv3(idx + 7, idx + 6, idx + 3));
	elements.push(uv3(idx + 0, idx + 2, idx + 4));
	elements.push(uv3(idx + 0, idx + 1, idx + 4));

	dirty = true;
}

chunk_vertex chunk_vertex::from_vec(v3 v, v3 uv, bv4 ao, u8 n_idx) { PROF

	LOG_DEBUG_ASSERT(v.x >= 0 && v.x < 256 && v.z >= 0 && v.z < 256 && v.y >= 0 && v.y < 4096 &&
					 uv.x >= 0 && uv.x < 256 && uv.y >= 0 && uv.y < 256 && uv.z >= 0 && uv.z < 4096 &&
					 ao.x >= 0 && ao.x < 4 && ao.y >= 0 && ao.y < 4 && ao.z >= 0 && ao.z < 4 && ao.w >= 0 && ao.w < 4);

	chunk_vertex ret;

	ret.v = (u8)uv.y;
	ret.u = (u8)uv.x;
	ret.z = (u8)v.z;
	ret.x = (u8)v.x;

	ret.aoty |= (u8)ao.w << 0;
	ret.aoty |= (u8)ao.z << 2;
	ret.aoty |= (u8)ao.y << 4;
	ret.aoty |= (u8)ao.x << 6;

	ret.aoty |= (u16)uv.z << 8;
	ret.aoty |= (u16)v.y  << 20;

	ret.ln |= n_idx << 24;

	return ret;
}

mesh_chunk mesh_chunk::make_cpu(u32 verts, allocator* alloc) { PROF

	if(alloc == null) {
		alloc = CURRENT_ALLOC();
	}

	mesh_chunk ret;

	ret.vertices = vector<chunk_vertex>::make(verts, alloc);
	ret.elements = vector<uv3>::make(verts, alloc);

	return ret;
}

void mesh_chunk::init_gpu() { PROF

	gpu = eng->ogl.add_object(FPTR(setup_mesh_chunk), FPTR(update_mesh_chunk), this);
}

void mesh_chunk::swap_mesh(mesh_chunk other) { PROF

	vertices.destroy();
	elements.destroy();

	vertices = other.vertices;
	elements = other.elements;

	dirty = true;
}

void mesh_chunk::destroy() { PROF

	vertices.destroy();
	elements.destroy();

	eng->ogl.destroy_object(gpu);
	gpu = -1;
}

void mesh_chunk::free_cpu() { PROF

	vertices.resize(0);
	elements.resize(0);
}

void mesh_chunk::clear() { PROF

	vertices.clear();
	elements.clear();

	dirty = true;
}

void mesh_chunk::unit_quad(v3 p1, v3 p2, v3 p3, v3 p4, v3 uv_ext, bv4 ao, u8 n_idx) { PROF

	u32 idx = vertices.size;

	const f32 v = (f32)chunk::units_per_voxel;

	vertices.push(chunk_vertex::from_vec(p1 * v, v3(0.0f, 0.0f, uv_ext.z), ao, n_idx));
	vertices.push(chunk_vertex::from_vec(p2 * v, v3(uv_ext.x * v, 0.0f, uv_ext.z), ao, n_idx));
	vertices.push(chunk_vertex::from_vec(p3 * v, v3(0.0f, uv_ext.y * v, uv_ext.z), ao, n_idx));
	vertices.push(chunk_vertex::from_vec(p4 * v, v3(uv_ext.x * v, uv_ext.y * v, uv_ext.z), ao, n_idx));

	elements.push(uv3(idx, idx + 1, idx + 2));
	elements.push(uv3(idx + 3, idx + 2, idx + 1));

	dirty = true;
}

void mesh_chunk::cube_no_norm(v3 pos, f32 len) { PROF

	u32 idx = vertices.size;

	f32 len2 = len / 2.0f;
	pos += {len2, len2, len2};

	vertices.push(chunk_vertex::from_vec(pos + v3( len2,  len2,  len2), v3(0,0,0), bv4(), 0));
	vertices.push(chunk_vertex::from_vec(pos + v3(-len2,  len2,  len2), v3(1,0,0), bv4(), 0));
	vertices.push(chunk_vertex::from_vec(pos + v3( len2, -len2,  len2), v3(0,1,0), bv4(), 0));
	vertices.push(chunk_vertex::from_vec(pos + v3( len2,  len2, -len2), v3(0,0,0), bv4(), 0));
	vertices.push(chunk_vertex::from_vec(pos + v3(-len2, -len2,  len2), v3(1,0,0), bv4(), 0));
	vertices.push(chunk_vertex::from_vec(pos + v3( len2, -len2, -len2), v3(0,1,0), bv4(), 0));
	vertices.push(chunk_vertex::from_vec(pos + v3(-len2,  len2, -len2), v3(1,0,0), bv4(), 0));
	vertices.push(chunk_vertex::from_vec(pos + v3(-len2, -len2, -len2), v3(1,1,0), bv4(), 0));

	elements.push(uv3(idx + 0, idx + 3, idx + 5));
	elements.push(uv3(idx + 0, idx + 3, idx + 6));
	elements.push(uv3(idx + 0, idx + 1, idx + 6));
	elements.push(uv3(idx + 1, idx + 4, idx + 7));
	elements.push(uv3(idx + 1, idx + 6, idx + 7));
	elements.push(uv3(idx + 4, idx + 2, idx + 5));
	elements.push(uv3(idx + 4, idx + 7, idx + 5));
	elements.push(uv3(idx + 7, idx + 5, idx + 3));
	elements.push(uv3(idx + 7, idx + 6, idx + 3));
	elements.push(uv3(idx + 0, idx + 2, idx + 4));
	elements.push(uv3(idx + 0, idx + 1, idx + 4));

	dirty = true;
}